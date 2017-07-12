#ifndef Raw_VideoPacketSource_H
#define Raw_VideoPacketSource_H


#include "scy/base.h"
#include "scy/packetsignal.h"

#ifdef HAVE_FFMPEG

#include "scy/av/packet.h"

#include "webrtc/media/base/videocapturer.h"


namespace scy {
namespace wrtc {


class RawVideoPacketSource : public cricket::VideoCapturer
{
public:
    RawVideoPacketSource(int width, int height, int fps, uint32_t fourcc);
    RawVideoPacketSource(const cricket::VideoFormat& captureFormat);
    virtual ~RawVideoPacketSource();

    /// Set the source `av::VideoPacket` emitter.
    /// The pointer is not managed by this class.
    void setPacketSource(PacketSignal* source);

    /// Callback that fired when an
    /// is ready for processing.
    void onVideoCaptured(av::VideoPacket& packet);

    /// cricket::VideoCapturer implementation.
    virtual cricket::CaptureState Start(const cricket::VideoFormat& capture_format) override;
    virtual void Stop() override;
    virtual bool GetPreferredFourccs(std::vector<uint32_t>* fourccs) override;
    virtual bool GetBestCaptureFormat(const cricket::VideoFormat& desired,
                                      cricket::VideoFormat* best_format) override;
    virtual bool IsRunning() override;
    virtual bool IsScreencast() const override;

protected:
    cricket::VideoFormat _captureFormat;
    webrtc::VideoRotation _rotation;
    int64_t _timestampOffset;
    int64_t _nextTimestamp;
    PacketSignal* _source;
};

} } // namespace scy::wrtc


#endif // HAVE_FFMPEG
#endif
