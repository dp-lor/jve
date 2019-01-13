

#ifndef JVESINGLERESOURCEITEMMODEL_H
#define JVESINGLERESOURCEITEMMODEL_H


#include "jveSourcesItemModel.h"


class jveSingleResourceItemModel : public jveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit jveSingleResourceItemModel(
                  jveApplication *app,
                  QDomElement     domElement,
            const int             type
        );
        virtual ~jveSingleResourceItemModel(void);
    protected:
        void initByResource(const QString &resourcePath);
};


#endif // JVESINGLERESOURCEITEMMODEL_H


