

#ifndef JVEGUIABOUTJVEBOX_H
#define JVEGUIABOUTJVEBOX_H


#include <QMessageBox>


class QEvent;


class JveGuiAboutJveBox : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  JveGuiAboutJveBox(QWidget *parent);
        virtual  ~JveGuiAboutJveBox(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIABOUTJVEBOX_H


