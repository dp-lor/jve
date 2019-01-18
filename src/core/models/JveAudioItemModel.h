

#ifndef JVEAUDIOITEMMODEL_H
#define JVEAUDIOITEMMODEL_H


#include "JveSingleResourceItemModel.h"


class JveAudioItemModel : public JveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit JveAudioItemModel(
            JveProject  *project,
            QDomElement  domElement
        );
        virtual ~JveAudioItemModel(void);
    private:
        // members
        QDomElement mp_audioDomElement;
        QString     mp_audioPath;
};


#endif // JVEAUDIOITEMMODEL_H


