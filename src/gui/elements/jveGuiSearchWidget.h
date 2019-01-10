

#ifndef JVEGUISEARCHWIDGET_H
#define JVEGUISEARCHWIDGET_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>


#include "jveGuiToolButton.h"


class jveGuiSearchWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiSearchWidget(QWidget *parent);
        virtual  ~jveGuiSearchWidget(void);
    public:
        // members
        QLineEdit searchInput;
    private:
        // members
        QHBoxLayout      mp_layout;
        jveGuiToolButton mp_searchIcon;
};


#endif // JVEGUISEARCHWIDGET_H


