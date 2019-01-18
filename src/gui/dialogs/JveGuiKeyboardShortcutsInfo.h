

#ifndef JVEGUIKEYBOARDSHORTCUTSINFO_H
#define JVEGUIKEYBOARDSHORTCUTSINFO_H


#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>


class QEvent;


class JveGuiKeyboardShortcutsInfo : public QDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiKeyboardShortcutsInfo(QWidget *parent);
        virtual  ~JveGuiKeyboardShortcutsInfo(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        QVBoxLayout  mp_layout;
        QLabel       mp_label;
        QTableWidget mp_table;
};


#endif // JVEGUIKEYBOARDSHORTCUTSINFO_H


