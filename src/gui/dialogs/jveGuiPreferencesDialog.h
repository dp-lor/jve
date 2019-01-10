

#ifndef JVEGUIPREFERENCESDIALOG_H
#define JVEGUIPREFERENCESDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QTabWidget>


class jveGuiPreferencesDialog : public QDialog
{
    Q_OBJECT
    public:
        explicit  jveGuiPreferencesDialog(QWidget *parent);
        virtual  ~jveGuiPreferencesDialog(void);
    private:
        QVBoxLayout *mp_layout;
        QTabWidget  *mp_mainTabs;
};


#endif // JVEGUIPREFERENCESDIALOG_H


