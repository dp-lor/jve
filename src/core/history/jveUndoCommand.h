

#ifndef JVEUNDOCOMMAND_H
#define JVEUNDOCOMMAND_H


#include <QList>


#include "../definitions/jveUndoCommandType.h"


class jveUndoCommandInfo;


class jveUndoCommand
{
    public:
        explicit jveUndoCommand(
            const int             type,
                  jveUndoCommand *parent = Q_NULLPTR
        );
        virtual ~jveUndoCommand(void);
    public:
        int  type(void) const;
        int  childrenCount(void) const;
    public:
        jveUndoCommand * childAt(const int i);
    public:
        void appendChild(jveUndoCommand *child);
    public:
        void undoChildren(void);
        void redoChildren(void);
    public:
        virtual void undo(void) = 0;
        virtual void redo(void) = 0;
        virtual bool isEqual(jveUndoCommand *command) = 0;
    public:
        virtual jveUndoCommandInfo * info(void) = 0;
    protected:
        // members
        bool                     mp_lockItself;
        int                      mp_type;
        jveUndoCommand          *mp_parent;
        QList<jveUndoCommand *>  mp_children;
};


#endif // JVEUNDOCOMMAND_H
