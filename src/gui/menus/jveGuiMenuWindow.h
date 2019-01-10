

#ifndef JVEGUIMENUWINDOW_H
#define JVEGUIMENUWINDOW_H


#include <QMenu>
#include <QEvent>


class jveGuiMenuWindow : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuWindow(QWidget *parent);
        virtual  ~jveGuiMenuWindow(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIMENUWINDOW_H


