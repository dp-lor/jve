

#ifndef JVEPROJECTROOTMODEL_H
#define JVEPROJECTROOTMODEL_H


#include "JveBaseModel.h"


class JveProject;

class JveSettingsModel;
class JveSourcesModel;
class JveTreeModel;
class JveStateModel;


class JveProjectRootModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit JveProjectRootModel(
            JveProject  *project,
            QDomElement  domElement
        );
        virtual ~JveProjectRootModel(void);
    public:
        void setUp(void);
    private:
        // members
        JveSettingsModel *mp_settings;
        JveSourcesModel  *mp_sources;
        JveTreeModel     *mp_tree;
        JveStateModel    *mp_state;
};


#endif // JVEPROJECTROOTMODEL_H


