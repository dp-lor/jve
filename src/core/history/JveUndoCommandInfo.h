

#ifndef JVEUNDOCOMMANDINFO_H
#define JVEUNDOCOMMANDINFO_H


#include <QString>


#include "../definitions/JveUndoCommandType.h"


class JveUndoCommandInfo
{
    public:
        explicit  JveUndoCommandInfo(const int type);
        virtual  ~JveUndoCommandInfo(void);
    public:
        int  type(void) const;
        void setText(const QString &text);
    public:
        virtual QString text(void) const = 0;
    protected:
        // members
        int     mp_type;
        QString mp_text;
};


#endif // JVEUNDOCOMMANDINFO_H
