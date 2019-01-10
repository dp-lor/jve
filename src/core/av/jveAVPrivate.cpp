

#include "jveAVPrivate.h"


#include <QThread>
#include <QDebug>


#include "../definitions/jveAVOptions.h"
#include "../utils/jveMathUtils.h"


extern "C" {

    #include "libavformat/avformat.h"

}


extern "C" {


static const AVCodec *next_codec_for_id(enum AVCodecID id, const AVCodec *prev,
                                        int encoder)
{
    while ((prev = av_codec_next(prev))) {
        if (prev->id == id &&
            (encoder ? av_codec_is_encoder(prev) : av_codec_is_decoder(prev)))
            return prev;
    }
    return NULL;
}

static void print_codecs_for_id(enum AVCodecID id, int encoder)
{
    const AVCodec *codec = NULL;

    printf(" (%s: ", encoder ? "encoders" : "decoders");

    while ((codec = next_codec_for_id(id, codec, encoder)))
        printf("%s ", codec->name);

    printf(")");
}


}


jveAVPrivate jveAV;


jveAVPrivate::jveAVPrivate(void)
{
    // project settings video sizes
    //buildProjectSettingsVideoSizes();

    // init libav
    avcodec_register_all();
    #if CONFIG_AVDEVICE
        avdevice_register_all();
    #endif
    //avfilter_register_all();
    av_register_all();
    avformat_network_init();


    return;


    // get available codecs
    const AVCodecDescriptor *desc = NULL;
    while ((desc = avcodec_descriptor_next(desc))) {


        const AVCodec *codec = NULL;

        printf(avcodec_find_decoder(desc->id) ? "D" : ".");
        printf(avcodec_find_encoder(desc->id) ? "E" : ".");

        switch (desc->type) {
            case AVMEDIA_TYPE_VIDEO:    printf("%c", 'V');
            case AVMEDIA_TYPE_AUDIO:    printf("%c", 'A');
            case AVMEDIA_TYPE_SUBTITLE: printf("%c", 'S');
            default:                    printf("%c", '?');
        }

        printf((desc->props & AV_CODEC_PROP_INTRA_ONLY) ? "I" : ".");
        printf((desc->props & AV_CODEC_PROP_LOSSY)      ? "L" : ".");
        printf((desc->props & AV_CODEC_PROP_LOSSLESS)   ? "S" : ".");

        printf(" %-20s %s", desc->name, desc->long_name ? desc->long_name : "");

        /* print decoders/encoders when there's more than one or their
         * names are different from codec name */
        while ((codec = next_codec_for_id(desc->id, codec, 0))) {
            if (strcmp(codec->name, desc->name)) {
                print_codecs_for_id(desc->id, 0);
                break;
            }
        }
        codec = NULL;
        while ((codec = next_codec_for_id(desc->id, codec, 1))) {
            if (strcmp(codec->name, desc->name)) {
                print_codecs_for_id(desc->id, 1);
                break;
            }
        }

        printf("\n");



    }

    // get available codecs stupid
    /*AVCodec *codec = av_codec_next(NULL);
    while (NULL != codec) {
        qDebug()
            << endl << "name --> " << codec->name
            << endl << "long_name --> " << codec->long_name
            << endl << "type --> " << codec->type
            << endl << "id --> " << codec->id
            // video
            << endl << "supported_framerates --> " << codec->supported_framerates
            << endl << "pix_fmts --> " << codec->pix_fmts
            // audio
            << endl << "supported_samplerates --> " << codec->supported_samplerates
            << endl << "sample_fmts --> " << codec->sample_fmts
            << endl << "channel_layouts --> " << codec->channel_layouts
            // predefined profiles (settings)
            << endl << "profiles --> " << codec->profiles
            << endl;
        codec = av_codec_next(codec);
    }*/

    // get available input formats list
    /*AVInputFormat *inputFormat = av_iformat_next(NULL);
    while (NULL != inputFormat) {
        qDebug()
            << endl << "name --> " << inputFormat->name
            << endl << "long_name --> " << inputFormat->long_name
            << endl << "extensions --> " << inputFormat->extensions
            << endl << "codec_tag --> " << inputFormat->codec_tag
            << endl << "raw_codec_id --> " << inputFormat->raw_codec_id
            << endl;
        inputFormat = av_iformat_next(inputFormat);
    }*/

    // get available output formats list
    /*AVOutputFormat *outputFormat = av_oformat_next(NULL);
    while (NULL != outputFormat) {
        qDebug()
            << endl << "name --> " << outputFormat->name
            << endl << "long_name --> " << outputFormat->long_name
            << endl << "extensions --> " << outputFormat->extensions
            << endl << "audio_codec --> " << outputFormat->audio_codec
            << endl << "video_codec --> " << outputFormat->video_codec
            << endl << "subtitle_codec --> " << outputFormat->subtitle_codec
            << endl;
        outputFormat = av_oformat_next(outputFormat);
    }*/
}

jveAVPrivate::~jveAVPrivate(void)
{
}

QMap<QString, const char *> &
jveAVPrivate::getProjectSettingsVideoSizes(void)
{
    return mp_projectSettingsVideoSizes;
}

void
jveAVPrivate::buildProjectSettingsVideoSizes(void)
{
    int length = (sizeof jveVideoSizes / sizeof jveVideoSizes[0]);

    for (int i = 0; i < length; i += 1) {
        jveVideoSizeEntry entry = jveVideoSizes[i];
        if (0 == entry.available) {
            continue;
        }
        int d = jveMathUtils::getGreatestCommonDivisor(entry.width, entry.height);
        mp_projectSettingsVideoSizes.insert(
            QString("%1x%2 (%3:%4 %5)")
                .arg(entry.width)
                .arg(entry.height)
                .arg(entry.width  / d)
                .arg(entry.height / d)
                .arg(entry.abbr),
            entry.abbr
        );
    }
}


