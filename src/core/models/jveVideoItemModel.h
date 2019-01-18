

#ifndef JVEVIDEOITEMMODEL_H
#define JVEVIDEOITEMMODEL_H


#include "jveSingleResourceItemModel.h"


class jveVideoItemModel : public jveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit jveVideoItemModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveVideoItemModel(void);
    private:
        // members
        QDomElement mp_videoDomElement;
        QString     mp_videoPath;
};


#endif // JVEVIDEOITEMMODEL_H


