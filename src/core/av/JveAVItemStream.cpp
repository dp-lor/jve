

#include "JveAVItemStream.h"


#include <QDebug>


JveAVItemStream::JveAVItemStream(
    AVFormatContext *AVFContext,
    AVCodecContext  *AVCContext
) : mp_AVFContext(AVFContext),
        mp_AVCContext(AVCContext)
{
    //qDebug() << "Samplerate :" << mp_AVCContext->sample_rate;
    //qDebug() << "Channels   :" << mp_AVCContext->channels;
    //qDebug() << "Format     :" << mp_AVCContext->sample_fmt;
}

JveAVItemStream::~JveAVItemStream(void)
{
}


