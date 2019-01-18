

#ifndef JVESETRANGESTARTCOMMANDINFO_H
#define JVESETRANGESTARTCOMMANDINFO_H


#include "JveUndoCommandInfo.h"


class JveSetRangeStartCommandInfo : public JveUndoCommandInfo
{
    public:
        explicit JveSetRangeStartCommandInfo(
            const int oldRangeStart,
            const int newRangeStart
        );
        virtual ~JveSetRangeStartCommandInfo(void);
    public:
        QString text(void) const;
    private:
        // members
        int mp_oldRangeStart;
        int mp_newRangeStart;
};


#endif // JVESETRANGESTARTCOMMANDINFO_H
