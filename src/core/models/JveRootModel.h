

#ifndef JVEROOTMODEL_H
#define JVEROOTMODEL_H


#include "JveBaseModel.h"


class JveSettingsModel;
class JveSourcesModel;
class JveTreeModel;
class JveStateModel;


class JveRootModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveRootModel(QDomElement domElement);
        virtual  ~JveRootModel(void);
    public:
        JveSettingsModel * settingsModel(void);
        JveSourcesModel  * sourcesModel(void);
        JveTreeModel     * treeModel(void);
        JveStateModel    * stateModel(void);
    public:
        void setUp(void);
    private:
        // members
        JveSettingsModel *mp_settings;
        JveSourcesModel  *mp_sources;
        JveTreeModel     *mp_tree;
        JveStateModel    *mp_state;
};


#endif // JVEROOTMODEL_H


