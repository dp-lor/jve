

#include "jveAVItemStream.h"


#include <QDebug>


jveAVItemStream::jveAVItemStream(
    AVFormatContext *AVFContext,
    AVCodecContext  *AVCContext
) : mp_AVFContext(AVFContext),
        mp_AVCContext(AVCContext)
{
    //qDebug() << "Samplerate :" << mp_AVCContext->sample_rate;
    //qDebug() << "Channels   :" << mp_AVCContext->channels;
    //qDebug() << "Format     :" << mp_AVCContext->sample_fmt;
}

jveAVItemStream::~jveAVItemStream(void)
{
}


