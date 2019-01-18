

#ifndef JVEGUIMENUWINDOW_H
#define JVEGUIMENUWINDOW_H


#include <QMenu>
#include <QEvent>


class JveGuiMenuWindow : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuWindow(QWidget *parent);
        virtual  ~JveGuiMenuWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIMENUWINDOW_H


