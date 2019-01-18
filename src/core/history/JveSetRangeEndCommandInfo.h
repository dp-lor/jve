

#ifndef JVESETRANGEENDCOMMANDINFO_H
#define JVESETRANGEENDCOMMANDINFO_H


#include "JveUndoCommandInfo.h"


class JveSetRangeEndCommandInfo : public JveUndoCommandInfo
{
    public:
        explicit JveSetRangeEndCommandInfo(
            const int oldRangeEnd,
            const int newRangeEnd
        );
        virtual ~JveSetRangeEndCommandInfo(void);
    public:
        QString text(void) const;
    private:
        // members
        int mp_oldRangeEnd;
        int mp_newRangeEnd;
};


#endif // JVESETRANGEENDCOMMANDINFO_H
