

#ifndef JVEPROJECTSOURCESIMAGEITEM_H
#define JVEPROJECTSOURCESIMAGEITEM_H


#include "jveSingleResourceItemModel.h"


class jveProjectSourcesImageItem : public jveSingleResourceItemModel
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


