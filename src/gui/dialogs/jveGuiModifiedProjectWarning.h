

#ifndef JVEGUIMODIFIEDPROJECTWARNING_H
#define JVEGUIMODIFIEDPROJECTWARNING_H


#include <QMessageBox>


class QEvent;


class jveGuiModifiedProjectWarning : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  jveGuiModifiedProjectWarning(QWidget *parent);
        virtual  ~jveGuiModifiedProjectWarning(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIMODIFIEDPROJECTWARNING_H


