

#ifndef JVEPROJECTSOURCESAUDIOITEM_H
#define JVEPROJECTSOURCESAUDIOITEM_H


#include "jveProjectSourcesSingleResourceItemModel.h"


class jveProjectSourcesAudioItem
    : public jveProjectSourcesSingleResourceItemModel
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


