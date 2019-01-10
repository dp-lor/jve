

#ifndef JVEPROJECTLOADEDCOMMANDINFO_H
#define JVEPROJECTLOADEDCOMMANDINFO_H


#include "jveUndoCommandInfo.h"


class jveProjectLoadedCommandInfo : public jveUndoCommandInfo
{
    public:
        explicit jveProjectLoadedCommandInfo(void);
        virtual ~jveProjectLoadedCommandInfo(void);
    public:
        QString text(void) const;
};


#endif // JVEPROJECTLOADEDCOMMANDINFO_H
