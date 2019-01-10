

#ifndef JVEGUITOOLSPACER_H
#define JVEGUITOOLSPACER_H


#include <QWidget>


class jveGuiToolSpacer : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiToolSpacer(QWidget *parent, const int size = 1);
        virtual  ~jveGuiToolSpacer(void);
};


#endif // JVEGUITOOLSPACER_H


