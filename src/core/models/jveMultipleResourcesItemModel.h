

#ifndef JVEMULTIPLERESOURCESITEMMODEL_H
#define JVEMULTIPLERESOURCESITEMMODEL_H


#include "jveSourcesItemModel.h"


#include <QStringList>


class jveMultipleResourcesItemModel : public jveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveMultipleResourcesItemModel(
                  jveApplication *app,
                  QDomElement     domNode,
            const int             type
        );
        virtual ~jveMultipleResourcesItemModel(void);
    protected:
        void initByResources(
                const QString     &resourcesDirPath,
                const QStringList &resourcesList
        );
};


#endif // JVEMULTIPLERESOURCESITEMMODEL_H


