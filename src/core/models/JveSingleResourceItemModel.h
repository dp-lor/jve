

#ifndef JVESINGLERESOURCEITEMMODEL_H
#define JVESINGLERESOURCEITEMMODEL_H


#include "JveSourcesItemModel.h"


#include "../definitions/JveSourcesItemOption.h"


class JveSingleResourceItemModel : public JveSourcesItemModel
{
    Q_OBJECT
    public:
        explicit JveSingleResourceItemModel(
                  JveProject  *project,
                  QDomElement  domElement,
            const int          type
        );
        virtual ~JveSingleResourceItemModel(void);
    public:
        static QDomElement createItemDom(
                  QDomDocument &domDocument,
            const QString      &resourceTagName,
            const QString      &projectParentDirPath,
            const QString      &resourcePath
        );
    protected:
        void initByResource(const QString &resourcePath, const int options);
};


#endif // JVESINGLERESOURCEITEMMODEL_H


