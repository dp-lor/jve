

#ifndef JVEGUIOPENPROJECTDIALOG_H
#define JVEGUIOPENPROJECTDIALOG_H


#include <QFileDialog>


class QEvent;


class JveGuiOpenProjectDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiOpenProjectDialog(QWidget *parent);
        virtual  ~JveGuiOpenProjectDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIOPENPROJECTDIALOG_H


