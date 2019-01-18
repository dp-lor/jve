

#ifndef JVEGUISEARCHWIDGET_H
#define JVEGUISEARCHWIDGET_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>


#include "JveGuiToolButton.h"


class JveGuiSearchWidget : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiSearchWidget(QWidget *parent);
        virtual  ~JveGuiSearchWidget(void);
    public:
        // members
        QLineEdit searchInput;
    private:
        // members
        QHBoxLayout      mp_layout;
        JveGuiToolButton mp_searchIcon;
};


#endif // JVEGUISEARCHWIDGET_H


