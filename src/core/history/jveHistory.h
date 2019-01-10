

#ifndef JVEHISTORY_H
#define JVEHISTORY_H


#include <QObject>
#include <QList>


class jveApplication;
class jveUndoCommand;


class jveHistory : public QObject
{
    Q_OBJECT
    public:
        explicit  jveHistory(void);
        virtual  ~jveHistory(void);
    public:
        void setApplication(jveApplication *app);
        void clear(void);
        void setProjectLoadedState(void);
        void setNewProjectLoadedState(void);
        void appendUndoCommand(jveUndoCommand *undoCommand);
        void setUndoStackClean(void);
    private:
        void appendUndoCommandWithModifiedState(
                  jveUndoCommand *undoCommand,
            const bool            modified
        );
        bool isEqualUndoCommands(
            jveUndoCommand *firstCommand,
            jveUndoCommand *secondCommand
        ) const;
    private slots:
        void slotSetUndoStackCurrentIndex(const int index);
    private:
        // members
        jveApplication          *mp_app;
        int                      mp_undoStackCurrentIndex;
        int                      mp_undoStackCleanIndex;
        QList<jveUndoCommand *>  mp_undoStack;
};


#endif // JVEHISTORY_H


