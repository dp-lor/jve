

#ifndef JVEGUIPROJECTSOURCESVIEW_H
#define JVEGUIPROJECTSOURCESVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QString>


#include "JveGuiProjectSourcesViewBar.h"
#include "JveGuiProjectSourcesViewArea.h"


class QEvent;


class JveGuiProjectSourcesView : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesView(QWidget *parent);
        virtual  ~JveGuiProjectSourcesView(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotStateChanged(const int state);
        void slotResetView(void);
        void slotApplyItemsFilter(const QString &searchString);
    private:
        // members
        QVBoxLayout                  mp_layout;
        JveGuiProjectSourcesViewBar  mp_bar;
        JveGuiProjectSourcesViewArea mp_area;
};


#endif // JVEGUIPROJECTSOURCESVIEW_H


