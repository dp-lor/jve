

#ifndef JVEGUIOPENPROJECTDIALOG_H
#define JVEGUIOPENPROJECTDIALOG_H


#include <QFileDialog>


class QEvent;


class jveGuiOpenProjectDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  jveGuiOpenProjectDialog(QWidget *parent);
        virtual  ~jveGuiOpenProjectDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIOPENPROJECTDIALOG_H


