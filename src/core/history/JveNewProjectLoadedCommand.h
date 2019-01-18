

#ifndef JVENEWPROJECTLOADEDCOMMAND_H
#define JVENEWPROJECTLOADEDCOMMAND_H


#include "JveUndoCommand.h"


class JveNewProjectLoadedCommand : public JveUndoCommand
{
    public:
        explicit  JveNewProjectLoadedCommand(void);
        virtual  ~JveNewProjectLoadedCommand(void);
    public:
        void undo(void);
        void redo(void);
        bool isEqual(JveUndoCommand *command);
    public:
        JveUndoCommandInfo * info(void);
};


#endif // JVENEWPROJECTLOADEDCOMMAND_H
