#ifndef Sample_SampleMediaCapturer_H
#define Sample_SampleMediaCapturer_H


#include "scy/base.h"

#ifdef HAVE_FFMPEG

#include "scy/av/av.h"
#include "sample_mediacapture.h"
#include "scy/webrtc/audiopacketmodule.h"
#include "raw_videopacketsource.h"

#include "webrtc/api/peerconnectioninterface.h"


namespace scy {
namespace wrtc {


class SampleMediaCapturer
{
public:
    SampleMediaCapturer();
    ~SampleMediaCapturer();

    void openFile(const std::string& file, bool loop = true);

    void addMediaTracks(webrtc::PeerConnectionFactoryInterface* factory,
                        webrtc::MediaStreamInterface* stream);

    void start();
    void stop();

    rtc::scoped_refptr<AudioPacketModule> getAudioModule();
    RawVideoPacketSource* createVideoSource();

protected:
    PacketStream _stream;
    av::SampleMediaCapture::Ptr _videoCapture;
    rtc::scoped_refptr<AudioPacketModule> _audioModule;
};


} } // namespace scy::wrtc


#endif // HAVE_FFMPEG
#endif


/// @\}
