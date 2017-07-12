#ifndef Raw_VideoDecoder_H
#define Raw_VideoDecoder_H


#include "scy/base.h"

#ifdef HAVE_FFMPEG

#include "scy/av/packet.h"
#include "scy/av/videodecoder.h"


namespace scy {
namespace av {


struct RawVideoDecoder : public VideoDecoder
{
    RawVideoDecoder(AVStream* stream);

//    virtual void create() override;
//    virtual void open() override;
//    virtual void close() override;

    /// Fake decoding.
    virtual bool decode(AVPacket& ipacket);

//    /// Flushes buffered frames.
//    /// This method should be called after decoding
//    /// until false is returned.
//    virtual void flush();
};


} // namespace av
} // namespace scy


#endif
#endif // Raw_VideoDecoder_H

