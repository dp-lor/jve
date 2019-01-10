

#ifndef JVEPROJECTSOURCESVIDEOITEM_H
#define JVEPROJECTSOURCESVIDEOITEM_H


#include "jveProjectSourcesItemModel.h"


//#include "../av/jveAVItem.h"


class jveProjectSourcesVideoItem : public jveProjectSourcesItemModel
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
        //jveAVItem   mp_avItem;
};


#endif // JVEPROJECTSOURCESVIDEOITEM_H


