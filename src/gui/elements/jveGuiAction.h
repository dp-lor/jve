

#ifndef JVEGUIACTION_H
#define JVEGUIACTION_H


#include <QAction>


class jveGuiAction : public QAction
{
    Q_OBJECT
    public:
        explicit  jveGuiAction(QWidget *parent);
        virtual  ~jveGuiAction(void);
};


#endif // JVEGUIACTION_H


