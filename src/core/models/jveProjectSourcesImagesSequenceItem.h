

#ifndef JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H
#define JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H


#include "jveProjectSourcesItemModel.h"


class jveProjectSourcesImagesSequenceItem : public jveProjectSourcesItemModel
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
        QStringList mp_sequencePaths;
};


#endif // JVEPROJECTSOURCESIMAGESSEQUENCEITEM_H


