

#ifndef JVEVIDEOITEMMODEL_H
#define JVEVIDEOITEMMODEL_H


#include "JveSingleResourceItemModel.h"


class JveVideoItemModel : public JveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit JveVideoItemModel(
                  JveProject  *project,
                  QDomElement  domElement,
            const int          options
        );
        virtual ~JveVideoItemModel(void);
    private:
        // members
        QDomElement mp_videoDomElement;
        QString     mp_videoPath;
};


#endif // JVEVIDEOITEMMODEL_H


