

#ifndef JVESETRANGESTARTCOMMAND_H
#define JVESETRANGESTARTCOMMAND_H


#include "jveUndoCommand.h"


class jveSettingsModel;


class jveSetRangeStartCommand : public jveUndoCommand
{
    public:
        explicit jveSetRangeStartCommand(
                  jveSettingsModel *settingsModel,
            const int               oldRangeStart,
            const int               newRangeStart,
                  jveUndoCommand   *parent = Q_NULLPTR
        );
        virtual ~jveSetRangeStartCommand(void);
    public:
        int  oldRangeStart(void) const;
        int  newRangeStart(void) const;
        void undo(void);
        void redo(void);
        bool isEqual(jveUndoCommand *command);
    public:
        jveUndoCommandInfo * info(void);
    private:
        // members
        jveSettingsModel *mp_settingsModel;
        int               mp_oldRangeStart;
        int               mp_newRangeStart;
};


#endif // JVESETRANGESTARTCOMMAND_H
