

#ifndef JVEPROJECTSOURCESMULTIPLERESOURCESITEMMODEL_H
#define JVEPROJECTSOURCESMULTIPLERESOURCESITEMMODEL_H


#include "jveSourcesItemModel.h"


#include <QStringList>


class jveProjectSourcesMultipleResourcesItemModel : public jveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesMultipleResourcesItemModel(
                  jveApplication *app,
                  QDomElement     domNode,
            const int             type
        );
        virtual ~jveProjectSourcesMultipleResourcesItemModel(void);
    protected:
        void initByResources(const QStringList &resourcesList);
};


#endif // JVEPROJECTSOURCESMULTIPLERESOURCESITEMMODEL_H


