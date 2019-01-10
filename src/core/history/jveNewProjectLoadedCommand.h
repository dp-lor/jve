

#ifndef JVENEWPROJECTLOADEDCOMMAND_H
#define JVENEWPROJECTLOADEDCOMMAND_H


#include "jveUndoCommand.h"


class jveNewProjectLoadedCommand : public jveUndoCommand
{
    public:
        explicit  jveNewProjectLoadedCommand(void);
        virtual  ~jveNewProjectLoadedCommand(void);
    public:
        void undo(void);
        void redo(void);
        bool isEqual(jveUndoCommand *command);
    public:
        jveUndoCommandInfo * info(void);
};


#endif // JVENEWPROJECTLOADEDCOMMAND_H
