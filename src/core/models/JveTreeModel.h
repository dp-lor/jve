

#ifndef JVETREEMODEL_H
#define JVETREEMODEL_H


#include "JveBaseModel.h"


class JveTreeModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveTreeModel(QDomElement domElement);
        virtual  ~JveTreeModel(void);
};


#endif // JVETREEMODEL_H


