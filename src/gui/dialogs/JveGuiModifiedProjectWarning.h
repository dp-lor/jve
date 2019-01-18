

#ifndef JVEGUIMODIFIEDPROJECTWARNING_H
#define JVEGUIMODIFIEDPROJECTWARNING_H


#include <QMessageBox>


class QEvent;


class JveGuiModifiedProjectWarning : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  JveGuiModifiedProjectWarning(QWidget *parent);
        virtual  ~JveGuiModifiedProjectWarning(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIMODIFIEDPROJECTWARNING_H


