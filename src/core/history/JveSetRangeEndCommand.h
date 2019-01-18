

#ifndef JVESETRANGEENDCOMMAND_H
#define JVESETRANGEENDCOMMAND_H


#include "JveUndoCommand.h"


class JveSettingsModel;


class JveSetRangeEndCommand : public JveUndoCommand
{
    public:
        explicit JveSetRangeEndCommand(
                  JveSettingsModel *settingsModel,
            const int               oldRangeEnd,
            const int               newRangeEnd,
                  JveUndoCommand   *parent = nullptr
        );
        virtual ~JveSetRangeEndCommand(void);
    public:
        int  oldRangeEnd(void) const;
        int  newRangeEnd(void) const;
        void undo(void);
        void redo(void);
        bool isEqual(JveUndoCommand *command);
    public:
        JveUndoCommandInfo * info(void);
    private:
        // members
        JveSettingsModel *mp_settingsModel;
        int               mp_oldRangeEnd;
        int               mp_newRangeEnd;
};


#endif // JVESETRANGEENDCOMMAND_H
