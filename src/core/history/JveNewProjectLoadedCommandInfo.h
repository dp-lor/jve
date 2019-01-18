

#ifndef JVENEWPROJECTLOADEDCOMMANDINFO_H
#define JVENEWPROJECTLOADEDCOMMANDINFO_H


#include "JveUndoCommandInfo.h"


class JveNewProjectLoadedCommandInfo : public JveUndoCommandInfo
{
    public:
        explicit  JveNewProjectLoadedCommandInfo(void);
        virtual  ~JveNewProjectLoadedCommandInfo(void);
    public:
        QString text(void) const;
};


#endif // JVENEWPROJECTLOADEDCOMMANDINFO_H
