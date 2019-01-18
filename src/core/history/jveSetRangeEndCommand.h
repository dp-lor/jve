

#ifndef JVESETRANGEENDCOMMAND_H
#define JVESETRANGEENDCOMMAND_H


#include "jveUndoCommand.h"


class jveSettingsModel;


class jveSetRangeEndCommand : public jveUndoCommand
{
    public:
        explicit jveSetRangeEndCommand(
                  jveSettingsModel *settingsModel,
            const int               oldRangeEnd,
            const int               newRangeEnd,
                  jveUndoCommand   *parent = Q_NULLPTR
        );
        virtual ~jveSetRangeEndCommand(void);
    public:
        int  oldRangeEnd(void) const;
        int  newRangeEnd(void) const;
        void undo(void);
        void redo(void);
        bool isEqual(jveUndoCommand *command);
    public:
        jveUndoCommandInfo * info(void);
    private:
        // members
        jveSettingsModel *mp_settingsModel;
        int               mp_oldRangeEnd;
        int               mp_newRangeEnd;
};


#endif // JVESETRANGEENDCOMMAND_H
