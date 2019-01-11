

#ifndef JVEPROJECTSOURCESAUDIOITEM_H
#define JVEPROJECTSOURCESAUDIOITEM_H


#include "jveSingleResourceItemModel.h"


class jveProjectSourcesAudioItem : public jveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesAudioItem(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSourcesAudioItem(void);
    private:
        // members
        QDomElement mp_audioDomElement;
        QString     mp_audioPath;
};


#endif // JVEPROJECTSOURCESAUDIOITEM_H


