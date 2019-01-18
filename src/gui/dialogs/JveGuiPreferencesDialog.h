

#ifndef JVEGUIPREFERENCESDIALOG_H
#define JVEGUIPREFERENCESDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QTabWidget>


class JveGuiPreferencesDialog : public QDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiPreferencesDialog(QWidget *parent);
        virtual  ~JveGuiPreferencesDialog(void);
    private:
        QVBoxLayout *mp_layout;
        QTabWidget  *mp_mainTabs;
};


#endif // JVEGUIPREFERENCESDIALOG_H


