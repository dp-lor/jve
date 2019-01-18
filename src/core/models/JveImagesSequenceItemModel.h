

#ifndef JVEIMAGESSEQUENCEITEMMODEL_H
#define JVEIMAGESSEQUENCEITEMMODEL_H


#include "JveMultipleResourcesItemModel.h"


class JveImagesSequenceItemModel : public JveMultipleResourcesItemModel
{
    Q_OBJECT
    public:
        explicit JveImagesSequenceItemModel(
            JveProject  *project,
            QDomElement  domElement
        );
        virtual ~JveImagesSequenceItemModel(void);
    private:
        // members
        QDomElement          mp_sequenceDomElement;
        QString              mp_sequencePath;
        QVector<QDomElement> mp_sequenceItemsDomElements;
        QStringList          mp_sequenceItemsList;
};


#endif // JVEIMAGESSEQUENCEITEMMODEL_H


