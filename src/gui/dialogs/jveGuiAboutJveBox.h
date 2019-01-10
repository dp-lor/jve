

#ifndef JVEGUIABOUTJVEBOX_H
#define JVEGUIABOUTJVEBOX_H


#include <QMessageBox>


class QEvent;


class jveGuiAboutJveBox : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  jveGuiAboutJveBox(QWidget *parent);
        virtual  ~jveGuiAboutJveBox(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIABOUTJVEBOX_H


