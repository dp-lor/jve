

#ifndef JVEHISTORYSIGNALSPRIVATE_H
#define JVEHISTORYSIGNALSPRIVATE_H


#include <QObject>


class jveUndoCommandInfo;


class jveHistorySignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveHistorySignalsPrivate(void);
        virtual  ~jveHistorySignalsPrivate(void);
    signals:
        void undoStackChanged(
            const int                 stackSize,
            const int                 currentIndex,
            const int                 cleanIndex,
                  jveUndoCommandInfo *undoCommandInfo
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


