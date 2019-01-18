

#ifndef JVEUNDOCOMMAND_H
#define JVEUNDOCOMMAND_H


#include <QList>


#include "../definitions/JveUndoCommandType.h"


class JveUndoCommandInfo;


class JveUndoCommand
{
    public:
        explicit JveUndoCommand(
            const int             type,
                  JveUndoCommand *parent = nullptr
        );
        virtual ~JveUndoCommand(void);
    public:
        int  type(void) const;
        int  childrenCount(void) const;
    public:
        JveUndoCommand * childAt(const int i);
    public:
        void appendChild(JveUndoCommand *child);
    public:
        void undoChildren(void);
        void redoChildren(void);
    public:
        virtual void undo(void) = 0;
        virtual void redo(void) = 0;
        virtual bool isEqual(JveUndoCommand *command) = 0;
    public:
        virtual JveUndoCommandInfo * info(void) = 0;
    protected:
        // members
        bool                     mp_lockItself;
        int                      mp_type;
        JveUndoCommand          *mp_parent;
        QList<JveUndoCommand *>  mp_children;
};


#endif // JVEUNDOCOMMAND_H
