

#ifndef JVEAUDIOITEMMODEL_H
#define JVEAUDIOITEMMODEL_H


#include "jveSingleResourceItemModel.h"


class jveAudioItemModel : public jveSingleResourceItemModel
{
    Q_OBJECT
    public:
        explicit jveAudioItemModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveAudioItemModel(void);
    private:
        // members
        QDomElement mp_audioDomElement;
        QString     mp_audioPath;
};


#endif // JVEAUDIOITEMMODEL_H


