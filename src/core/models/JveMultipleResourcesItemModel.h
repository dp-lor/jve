

#ifndef JVEMULTIPLERESOURCESITEMMODEL_H
#define JVEMULTIPLERESOURCESITEMMODEL_H


#include "JveSourcesItemModel.h"


#include <QStringList>


class JveMultipleResourcesItemModel : public JveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit JveMultipleResourcesItemModel(
                  JveProject  *project,
                  QDomElement  domElement,
            const int          type
        );
        virtual ~JveMultipleResourcesItemModel(void);
    protected:
        void initByResources(
                const QString     &resourcesDirPath,
                const QStringList &resourcesList
        );
};


#endif // JVEMULTIPLERESOURCESITEMMODEL_H


