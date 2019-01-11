

#ifndef JVEPROJECTSOURCESVIDEOITEM_H
#define JVEPROJECTSOURCESVIDEOITEM_H


#include "jveSingleResourceItemModel.h"


class jveProjectSourcesVideoItem : public jveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesVideoItem(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSourcesVideoItem(void);
    private:
        // members
        QDomElement mp_videoDomElement;
        QString     mp_videoPath;
};


#endif // JVEPROJECTSOURCESVIDEOITEM_H


