

#ifndef JVESETRANGESTARTCOMMANDINFO_H
#define JVESETRANGESTARTCOMMANDINFO_H


#include "jveUndoCommandInfo.h"


class jveSetRangeStartCommandInfo : public jveUndoCommandInfo
{
    public:
        explicit jveSetRangeStartCommandInfo(
            const int oldRangeStart,
            const int newRangeStart
        );
        virtual ~jveSetRangeStartCommandInfo(void);
    public:
        QString text(void) const;
    private:
        // members
        int mp_oldRangeStart;
        int mp_newRangeStart;
};


#endif // JVESETRANGESTARTCOMMANDINFO_H
