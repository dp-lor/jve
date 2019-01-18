

#ifndef JVEPROJECTROOTMODEL_H
#define JVEPROJECTROOTMODEL_H


#include "jveBaseModel.h"


class jveProject;

class jveSettingsModel;
class jveSourcesModel;
class jveTreeModel;
class jveStateModel;


class jveProjectRootModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProjectRootModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveProjectRootModel(void);
    public:
        void setUp(void);
    private:
        // members
        jveSettingsModel *mp_settings;
        jveSourcesModel  *mp_sources;
        jveTreeModel     *mp_tree;
        jveStateModel    *mp_state;
};


#endif // JVEPROJECTROOTMODEL_H


