

#ifndef JVEPROJECT_H
#define JVEPROJECT_H


#include "jveBaseModel.h"


class jveProjectSettings;
class jveProjectState;
class jveProjectSources;
//class jveProjectTree;


class jveProject : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProject(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProject(void);
    public:
        void setUp(void);
    private:
        // members
        jveProjectSettings *mp_settings;
        jveProjectState    *mp_state;
        jveProjectSources  *mp_sources;
        //jveProjectTree     *mp_tree;
};


#endif // JVEPROJECT_H


