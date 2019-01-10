

#ifndef JVESETRANGEENDCOMMANDINFO_H
#define JVESETRANGEENDCOMMANDINFO_H


#include "jveUndoCommandInfo.h"


class jveSetRangeEndCommandInfo : public jveUndoCommandInfo
{
    public:
        explicit jveSetRangeEndCommandInfo(
            const int oldRangeEnd,
            const int newRangeEnd
        );
        virtual ~jveSetRangeEndCommandInfo(void);
    public:
        QString text(void) const;
    private:
        // members
        int mp_oldRangeEnd;
        int mp_newRangeEnd;
};


#endif // JVESETRANGEENDCOMMANDINFO_H
