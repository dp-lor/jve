

#ifndef JVEAVITEM_H
#define JVEAVITEM_H


#include <QString>
#include <QByteArray>
#include <QVector>


extern "C" {
    #include "libavformat/avformat.h"
}


#include "JveAVItemStream.h"


class JveAVItem
{
    public:
        explicit  JveAVItem(void);
        virtual  ~JveAVItem(void);
    public:
        void open(const QString &filePath);
        void close(void);
    private:
        void setErrorText(const int status);
    private:
        // members
        char                       mp_avErrorTextBuffer[255];
        bool                       mp_opened;
        int                        mp_avStatus;
        QByteArray                 mp_avFilePath;
        AVFormatContext           *mp_AVFContext;
        QVector<AVCodecContext *>  mp_videoStreams;
        QVector<JveAVItemStream *>  mp_audioStreams;
};


#endif // JVEAVITEM_H


