

#ifndef JVENEWPROJECTLOADEDCOMMANDINFO_H
#define JVENEWPROJECTLOADEDCOMMANDINFO_H


#include "jveUndoCommandInfo.h"


class jveNewProjectLoadedCommandInfo : public jveUndoCommandInfo
{
    public:
        explicit  jveNewProjectLoadedCommandInfo(void);
        virtual  ~jveNewProjectLoadedCommandInfo(void);
    public:
        QString text(void) const;
};


#endif // JVENEWPROJECTLOADEDCOMMANDINFO_H
