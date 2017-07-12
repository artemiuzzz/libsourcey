#include "sample_mediacapturer.h"

#ifdef HAVE_FFMPEG

#include "scy/av/audioresampler.h"
#include "scy/av/ffmpeg.h"
#include "scy/av/realtimepacketqueue.h"
#include "scy/filesystem.h"
#include "scy/logger.h"
#include "scy/webrtc/webrtc.h"
#include "webrtc/media/engine/webrtcvideocapturerfactory.h"
#include "webrtc/modules/video_capture/video_capture_factory.h"


namespace scy {
namespace wrtc {


SampleMediaCapturer::SampleMediaCapturer()
    : _videoCapture(std::make_shared<av::SampleMediaCapture>())
    , _audioModule(AudioPacketModule::Create())
{
    _stream.attachSource(_videoCapture, true);
    // _stream.attach(std::make_shared<av::RealtimePacketQueue<av::MediaPacket>>(0), 5);
    // _stream.attach(std::make_shared<av::RealtimePacketQueue<av::PlanarVideoPacket>>(0), 5);
    _stream.emitter += packetSlot(_audioModule.get(), &AudioPacketModule::onAudioCaptured);
}


SampleMediaCapturer::~SampleMediaCapturer()
{
}


void SampleMediaCapturer::openFile(const std::string& file, bool loop)
{
    // Open the capture file
    _videoCapture->setLoopInput(loop);
    _videoCapture->setRealtimePlayback(true);
    _videoCapture->openFile(file);

    // Set the output settings
    if (_videoCapture->audio()) {
        _videoCapture->audio()->oparams.sampleFmt = "s16";
        _videoCapture->audio()->oparams.sampleRate = 44000;
        _videoCapture->audio()->oparams.channels = 2;
        _videoCapture->audio()->recreateResampler();
        // _videoCapture->audio()->resampler->maxNumSamples = 440;
        // _videoCapture->audio()->resampler->variableOutput = false;
    }

    // Convert to yuv420p for WebRTC compatability
    if (_videoCapture->video()) {
        _videoCapture->video()->oparams.pixelFmt = "yuv420p"; // nv12
        // _videoCapture->video()->oparams.width = capture_format.width;
        // _videoCapture->video()->oparams.height = capture_format.height;
    }
}


RawVideoPacketSource *SampleMediaCapturer::createVideoSource()
{
    assert(_videoCapture->video());
    auto oparams = _videoCapture->video()->oparams;
    auto source = new RawVideoPacketSource(oparams.width, oparams.height,
                                           oparams.fps, cricket::FOURCC_I420);
    source->setPacketSource(&_stream.emitter); // nullified on VideoPacketSource::Stop
    return source;
}


rtc::scoped_refptr<AudioPacketModule> SampleMediaCapturer::getAudioModule()
{
    return _audioModule;
}


void SampleMediaCapturer::addMediaTracks(
    webrtc::PeerConnectionFactoryInterface* factory,
    webrtc::MediaStreamInterface* stream)
{
    // This capturer is multicast, meaning it can be used as the source
    // for multiple Peer objects.
    //
    // KLUDGE: Pixel format conversion should happen on the
    // VideoPacketSource rather than on the decoder becasue different
    // peers may request different optimal output video sizes.

    // Create and add the audio stream
    if (_videoCapture->audio()) {
        stream->AddTrack(factory->CreateAudioTrack(
            kAudioLabel, factory->CreateAudioSource(nullptr)));
    }

    // Create and add the video stream
    if (_videoCapture->video()) {
        stream->AddTrack(factory->CreateVideoTrack(
            kVideoLabel, factory->CreateVideoSource(createVideoSource(), nullptr)));
    }

    // Default WebRTC video stream for testing
    // stream->AddTrack(factory->CreateVideoTrack(
    //     kVideoLabel, factory->CreateVideoSource(openVideoDefaultWebRtcCaptureDevice(), nullptr)));
}


void SampleMediaCapturer::start()
{
    _stream.start();
}


void SampleMediaCapturer::stop()
{
    _stream.stop();
}


} } // namespace scy::wrtc


#endif // HAVE_FFMPEG

