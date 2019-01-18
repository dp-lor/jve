

#ifndef JVETREEMODEL_H
#define JVETREEMODEL_H


#include "jveBaseModel.h"


class jveProject;


class jveTreeModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit  jveTreeModel(jveProject *project, QDomElement domElement);
        virtual  ~jveTreeModel(void);
    private:
        // members
        jveProject *mp_project;
};


#endif // JVETREEMODEL_H


