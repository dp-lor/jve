

#ifndef JVEIMAGEITEMMODEL_H
#define JVEIMAGEITEMMODEL_H


#include "jveSingleResourceItemModel.h"


class jveImageItemModel : public jveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit jveImageItemModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveImageItemModel(void);
    private:
        // members
        QDomElement mp_imageDomElement;
        QString     mp_imagePath;
};


#endif // JVEIMAGEITEMMODEL_H


