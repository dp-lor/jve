

#ifndef JVESETRANGESTARTCOMMAND_H
#define JVESETRANGESTARTCOMMAND_H


#include "JveUndoCommand.h"


class JveSettingsModel;


class JveSetRangeStartCommand : public JveUndoCommand
{
    public:
        explicit JveSetRangeStartCommand(
                  JveSettingsModel *settingsModel,
            const int               oldRangeStart,
            const int               newRangeStart,
                  JveUndoCommand   *parent = nullptr
        );
        virtual ~JveSetRangeStartCommand(void);
    public:
        int  oldRangeStart(void) const;
        int  newRangeStart(void) const;
        void undo(void);
        void redo(void);
        bool isEqual(JveUndoCommand *command);
    public:
        JveUndoCommandInfo * info(void);
    private:
        // members
        JveSettingsModel *mp_settingsModel;
        int               mp_oldRangeStart;
        int               mp_newRangeStart;
};


#endif // JVESETRANGESTARTCOMMAND_H
