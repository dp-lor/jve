

#ifndef JVEGUIACTION_H
#define JVEGUIACTION_H


#include <QAction>


class JveGuiAction : public QAction
{
    Q_OBJECT
    public:
        explicit  JveGuiAction(QWidget *parent);
        virtual  ~JveGuiAction(void);
};


#endif // JVEGUIACTION_H


