

#ifndef JVEPROJECTSOURCESVIDEOITEM_H
#define JVEPROJECTSOURCESVIDEOITEM_H


#include "jveProjectSourcesSingleResourceItemModel.h"


class jveProjectSourcesVideoItem
    : public jveProjectSourcesSingleResourceItemModel
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


