

#ifndef JVEAVITEMSTREAM_H
#define JVEAVITEMSTREAM_H


extern "C" {
    #include "libavformat/avformat.h"
}


class jveAVItemStream
{
    public:
        explicit jveAVItemStream(
            AVFormatContext *AVFContext,
            AVCodecContext  *AVCContext
        );
        virtual ~jveAVItemStream(void);
    protected:
        // members
        int              mp_avStatus;
        AVFormatContext *mp_AVFContext;
        AVCodecContext  *mp_AVCContext;
};


#endif // JVEAVITEMSTREAM_H


