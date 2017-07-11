#ifndef Sample_MediaCapture_H
#define Sample_MediaCapture_H


#include "scy/base.h"

#ifdef HAVE_FFMPEG

//#include "scy/av/audiodecoder.h"
//#include "scy/av/ffmpeg.h"
//#include "scy/av/icapture.h"
//#include "scy/av/packet.h"
#include "raw_videodecoder.h"
//#include "scy/interface.h"
//#include "scy/packetsignal.h"

#include "scy/av/mediacapture.h"

namespace scy {
namespace av {


class SampleMediaCapture : public MediaCapture
{
public:
    typedef std::shared_ptr<SampleMediaCapture> Ptr;

    SampleMediaCapture();
    virtual ~SampleMediaCapture();

//    virtual void openFile(const std::string& file);
//    // #ifdef HAVE_FFMPEG_AVDEVICE
//    // virtual void openCamera(const std::string& device, int width = -1, int height = -1, double framerate = -1);
//    // virtual void openMicrophone(const std::string& device, int channels = -1, int sampleRate = -1);
//    // #endif
//    virtual void close();

//    virtual void start() override;
//    virtual void stop() override;

//    virtual void run() override;

//    virtual void getEncoderFormat(Format& format);
//    virtual void getEncoderAudioCodec(AudioCodec& params);
//    virtual void getEncoderVideoCodec(VideoCodec& params);

//    /// Continuously loop the input file when set
//    void setLoopInput(bool flag);

//    /// Playback video in real time when set
//    void setRealtimePlayback(bool flag);

//    AVFormatContext* formatCtx() const;
//    VideoDecoder* video() const;
//    AudioDecoder* audio() const;
//    bool stopping() const;
//    std::string error() const;

//    /// Signals that the capture thread is closing.
//    /// Careful, this signal is emitted from inside the tread contect.
//    NullSignal Closing;

protected:
    virtual void openStream(const std::string& filename, AVInputFormat* inputFormat, AVDictionary** formatParams);

    void emit(IPacket& packet);

protected:
//    mutable std::mutex _mutex;
//    Thread _thread;
//    AVFormatContext* _formatCtx;
//    VideoDecoder* _video;
//    AudioDecoder* _audio;
//    std::string _error;
//    bool _stopping;
//    bool _looping;
//    bool _realtime;
};


} // namespace av
} // namespace scy


#endif
#endif // Sample_MediaCapture_H

