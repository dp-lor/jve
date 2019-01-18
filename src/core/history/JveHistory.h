

#ifndef JVEHISTORY_H
#define JVEHISTORY_H


#include <QObject>
#include <QList>


class JveProject;
class JveUndoCommand;


class JveHistory : public QObject
{
    Q_OBJECT
    public:
        explicit  JveHistory(JveProject *project);
        virtual  ~JveHistory(void);
    public:
        void clear(void);
        void setProjectLoadedState(void);
        void setNewProjectLoadedState(void);
        void appendUndoCommand(JveUndoCommand *undoCommand);
        void setUndoStackClean(void);
    private:
        void appendUndoCommandWithModifiedState(
                  JveUndoCommand *undoCommand,
            const bool            modified
        );
        bool isEqualUndoCommands(
            JveUndoCommand *firstCommand,
            JveUndoCommand *secondCommand
        ) const;
    private slots:
        void slotSetUndoStackCurrentIndex(const int index);
    private:
        // members
        JveProject              *mp_project;
        int                      mp_undoStackCurrentIndex;
        int                      mp_undoStackCleanIndex;
        QList<JveUndoCommand *>  mp_undoStack;
};


#endif // JVEHISTORY_H


