

#ifndef JVEGUIBUTTON_H
#define JVEGUIBUTTON_H


#include <QPushButton>


class JveGuiButton : public QPushButton
{
    Q_OBJECT
    public:
        explicit  JveGuiButton(QWidget *parent);
        virtual  ~JveGuiButton(void);
};


#endif // JVEGUIBUTTON_H


