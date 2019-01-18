

#ifndef JVEPROJECTLOADEDCOMMANDINFO_H
#define JVEPROJECTLOADEDCOMMANDINFO_H


#include "JveUndoCommandInfo.h"


class JveProjectLoadedCommandInfo : public JveUndoCommandInfo
{
    public:
        explicit JveProjectLoadedCommandInfo(void);
        virtual ~JveProjectLoadedCommandInfo(void);
    public:
        QString text(void) const;
};


#endif // JVEPROJECTLOADEDCOMMANDINFO_H
