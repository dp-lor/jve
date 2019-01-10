

#ifndef JVEGUIBUTTON_H
#define JVEGUIBUTTON_H


#include <QPushButton>


class jveGuiButton : public QPushButton
{
    Q_OBJECT
    public:
        explicit  jveGuiButton(QWidget *parent);
        virtual  ~jveGuiButton(void);
};


#endif // JVEGUIBUTTON_H


