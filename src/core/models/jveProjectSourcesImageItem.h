

#ifndef JVEPROJECTSOURCESIMAGEITEM_H
#define JVEPROJECTSOURCESIMAGEITEM_H


#include "jveProjectSourcesItemModel.h"


class jveProjectSourcesImageItem : public jveProjectSourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesImageItem(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSourcesImageItem(void);
    private:
        // members
        QDomElement mp_imageDomElement;
        QString     mp_imagePath;
};


#endif // JVEPROJECTSOURCESIMAGEITEM_H


