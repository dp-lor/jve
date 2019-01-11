

#ifndef JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H
#define JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H


#include "jveSourcesItemModel.h"


class jveProjectSourcesSingleResourceItemModel : public jveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveProjectSourcesSingleResourceItemModel(
                  jveApplication *app,
                  QDomElement     domNode,
            const int             type
        );
        virtual ~jveProjectSourcesSingleResourceItemModel(void);
    protected:
        void initByResource(const QString &resourcePath);
};


#endif // JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H


