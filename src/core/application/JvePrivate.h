

#ifndef JVEPRIVATE_H
#define JVEPRIVATE_H


#include <QString>
#include <QDomDocument>


#include "../history/JveHistory.h"


class JveProjectRootModel;
class JveSettingsModel;
class JveSourcesModel;
class JveTreeModel;
class JveStateModel;


class JvePrivate
{
    public:
        explicit  JvePrivate(void);
        virtual  ~JvePrivate(void);
    public:
        JveHistory & history(void);
    private:
        // global application state
        int mp_state;
        // undo/redo history
        JveHistory mp_history;
        // project environment
        QString mp_projectParentDirPath;
        QString mp_projectFilePath;
        QString mp_projectFileName;
        // project data
        QDomDocument mp_domDocument;
        // shared project objects
        JveProjectRootModel *mp_rootModel;
        //JveRootModel     *mp_rootModel;
        JveSettingsModel *mp_settingsModel;
        JveSourcesModel  *mp_sourcesModel;
        JveTreeModel     *mp_treeModel;
        JveStateModel    *mp_stateModel;
};


#endif // JVEPRIVATE_H


