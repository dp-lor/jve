

#ifndef JVETREEMODEL_H
#define JVETREEMODEL_H


#include "JveBaseModel.h"


class JveProject;


class JveTreeModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveTreeModel(JveProject *project, QDomElement domElement);
        virtual  ~JveTreeModel(void);
    private:
        // members
        JveProject *mp_project;
};


#endif // JVETREEMODEL_H


