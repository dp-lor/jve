

#ifndef JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H
#define JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H


#include "jveMultipleResourcesItemModel.h"


class jveProjectSourcesImagesSequenceItem : public jveMultipleResourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesImagesSequenceItem(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSourcesImagesSequenceItem(void);
    private:
        // members
        QDomElement          mp_sequenceDomElement;
        QString              mp_sequencePath;
        QVector<QDomElement> mp_sequenceItemsDomElements;
        QStringList          mp_sequenceItemsList;
};


#endif // JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H


