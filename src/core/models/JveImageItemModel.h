

#ifndef JVEIMAGEITEMMODEL_H
#define JVEIMAGEITEMMODEL_H


#include "JveSingleResourceItemModel.h"


class JveImageItemModel : public JveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit JveImageItemModel(
            JveProject  *project,
            QDomElement  domElement
        );
        virtual ~JveImageItemModel(void);
    private:
        // members
        QDomElement mp_imageDomElement;
        QString     mp_imagePath;
};


#endif // JVEIMAGEITEMMODEL_H


