

#ifndef JVEHISTORYSIGNALSPRIVATE_H
#define JVEHISTORYSIGNALSPRIVATE_H


#include <QObject>


class JveUndoCommandInfo;


class JveHistorySignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  JveHistorySignalsPrivate(void);
        virtual  ~JveHistorySignalsPrivate(void);
    signals:
        void undoStackChanged(
            const int                 stackSize,
            const int                 currentIndex,
            const int                 cleanIndex,
                  JveUndoCommandInfo *undoCommandInfo
        );
        void historyActionsStateChanged(
            const bool canUndo,
            const bool canRedo
        );
        void wantSetUndoStackCurrentIndex(const int index);
        void wantUndo(void);
        void wantRedo(void);
};


#endif // JVEHISTORYSIGNALSPRIVATE_H


