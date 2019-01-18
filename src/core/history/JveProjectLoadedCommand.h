

#ifndef JVEPROJECTLOADEDCOMMAND_H
#define JVEPROJECTLOADEDCOMMAND_H


#include "JveUndoCommand.h"


class JveProjectLoadedCommand : public JveUndoCommand
{
    public:
        explicit JveProjectLoadedCommand(void);
        virtual ~JveProjectLoadedCommand(void);
    public:
        void undo(void);
        void redo(void);
        bool isEqual(JveUndoCommand *command);
    public:
        JveUndoCommandInfo * info(void);
};


#endif // JVEPROJECTLOADEDCOMMAND_H
