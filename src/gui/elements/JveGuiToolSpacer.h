

#ifndef JVEGUITOOLSPACER_H
#define JVEGUITOOLSPACER_H


#include <QWidget>


class JveGuiToolSpacer : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiToolSpacer(QWidget *parent, const int size = 1);
        virtual  ~JveGuiToolSpacer(void);
};


#endif // JVEGUITOOLSPACER_H


