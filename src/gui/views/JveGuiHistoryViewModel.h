

#ifndef JVEGUIHISTORYVIEWMODEL_H
#define JVEGUIHISTORYVIEWMODEL_H


#include <QAbstractListModel>
#include <QMutex>
#include <QItemSelectionModel>
#include <QList>
#include <QIcon>
#include <QPixmap>
#include <QBitmap>


class JveUndoCommandInfo;


class JveGuiHistoryViewModel : public QAbstractListModel
{
    Q_OBJECT
    public:
        explicit  JveGuiHistoryViewModel(QObject *parent);
        virtual  ~JveGuiHistoryViewModel(void);
    public:
        int      rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
    public:
        void updateIcons(void);
        void updateTranslations(void);
    private:
        void clear(void);
        void updateCommandInfoText(JveUndoCommandInfo *commandInfo);
    private slots:
        void slotChangeUndoStack(
            const int                 stackSize,
            const int                 currentIndex,
            const int                 cleanIndex,
                  JveUndoCommandInfo *undoCommandInfo
        );
        void slotUndo(void);
        void slotRedo(void);
        void slotCatchCurrentChanged(const QModelIndex &currentIndex);
    public:
        // members
        QItemSelectionModel selectionModel;
    private:
        // members
        QMutex                       mp_infoStackMutex;
        QList<JveUndoCommandInfo *>  mp_infoStack;
        bool                         mp_userCanChangeStack;
        int                          mp_currentIndex;
        int                          mp_cleanIndex;
        QIcon                        mp_dummyIcon;
        QPixmap                      mp_cleanIconPixmap;
        QBitmap                      mp_cleanIconMask;
};


#endif // JVEGUIHISTORYVIEWMODEL_H


