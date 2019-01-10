

#include "jveAVItem.h"


#include <QDebug>


jveAVItem::jveAVItem(void)
    : mp_opened(false),
        mp_avStatus(0),
        mp_AVFContext(NULL)
{
}

jveAVItem::~jveAVItem(void)
{
    close();
}

void
jveAVItem::open(const QString &filePath)
{
    // store file path
    mp_avFilePath = filePath.toLatin1();

    // close before opening
    if (mp_opened) {
        close();
    }

    // open file
    //mp_AVFContext = avformat_alloc_context();
    mp_avStatus = avformat_open_input(
        &mp_AVFContext,
        mp_avFilePath.data(),
        NULL,
        NULL
    );
    if (0 > mp_avStatus) {
        setErrorText(mp_avStatus);
        //qDebug() << mp_avErrorTextBuffer << mp_avFilePath;
        return;
    }

    // init streams info
    mp_avStatus = avformat_find_stream_info(mp_AVFContext, NULL);
    if (0 > mp_avStatus) {
        setErrorText(mp_avStatus);
        //qDebug() << mp_avErrorTextBuffer;
        return;
    }

    // find streams

    AVCodecContext *codecContext;
    int32_t         codecType;
    AVCodec        *codec;

    for (uint32_t i = 0; i < mp_AVFContext->nb_streams; i += 1) {

        codecContext = mp_AVFContext->streams[i]->codec;
        codecType    = codecContext->codec_type;

        // find decoder
        codec = avcodec_find_decoder(codecContext->codec_id);
        if (NULL == codec) {
            continue;
        }
        // we can handle truncated bitstreams
        if(codec->capabilities & CODEC_CAP_TRUNCATED) {
            codecContext->flags |= CODEC_FLAG_TRUNCATED;
        }
        // open decoder by codec type
        switch (codecType) {

            case AVMEDIA_TYPE_VIDEO:
                //qDebug() << "video found!";
            break;
            case AVMEDIA_TYPE_AUDIO:
                {
                    mp_avStatus = avcodec_open2(codecContext, codec, NULL);
                    if (0 > mp_avStatus) {
                        setErrorText(mp_avStatus);
                        //qDebug() << mp_avErrorTextBuffer;
                        continue;
                    }
                    mp_audioStreams.append(
                        new jveAVItemStream(mp_AVFContext, codecContext)
                    );
                }
            break;

        }

    } // each nb_streams

    //qDebug() << mp_AVFContext->bit_rate;
    //qDebug() << ( mp_AVFContext->duration - (mp_AVFContext->duration % 60) );
    //qDebug() << mp_videoStreams.size() << mp_audioStreams.size();

    mp_opened = true;
}

void
jveAVItem::close(void)
{
    if (mp_opened) {

        avformat_close_input(&mp_AVFContext);
        avformat_free_context(mp_AVFContext);

        mp_opened = false;
    }
}

void
jveAVItem::setErrorText(const int status)
{
    av_strerror(
        status,
        mp_avErrorTextBuffer,
        sizeof(mp_avErrorTextBuffer)
    );
}


