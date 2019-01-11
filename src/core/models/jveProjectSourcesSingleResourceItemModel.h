

#ifndef JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H
#define JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H


#include "jveProjectSourcesItemModel.h"


class jveProjectSourcesSingleResourceItemModel
    : public jveProjectSourcesItemModel
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
        void initResource(const QString &resourcePath);
};


#endif // JVEPROJECTSOURCESSINGLERESOURCEITEMMODEL_H


