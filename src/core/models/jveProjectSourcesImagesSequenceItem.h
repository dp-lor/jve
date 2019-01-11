

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
        QStringList mp_sequenceList;
};


#endif // JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H


