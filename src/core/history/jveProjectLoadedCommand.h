

#ifndef JVEPROJECTLOADEDCOMMAND_H
#define JVEPROJECTLOADEDCOMMAND_H


#include "jveUndoCommand.h"


class jveProjectLoadedCommand : public jveUndoCommand
{
    public:
        explicit jveProjectLoadedCommand(void);
        virtual ~jveProjectLoadedCommand(void);
    public:
        void undo(void);
        void redo(void);
        bool isEqual(jveUndoCommand *command);
    public:
        jveUndoCommandInfo * info(void);
};


#endif // JVEPROJECTLOADEDCOMMAND_H
