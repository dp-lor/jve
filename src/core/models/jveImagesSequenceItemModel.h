

#ifndef JVEIMAGESSEQUENCEITEMMODEL_H
#define JVEIMAGESSEQUENCEITEMMODEL_H


#include "jveMultipleResourcesItemModel.h"


class jveImagesSequenceItemModel : public jveMultipleResourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveImagesSequenceItemModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveImagesSequenceItemModel(void);
    private:
        // members
        QDomElement          mp_sequenceDomElement;
        QString              mp_sequencePath;
        QVector<QDomElement> mp_sequenceItemsDomElements;
        QStringList          mp_sequenceItemsList;
};


#endif // JVEIMAGESSEQUENCEITEMMODEL_H


