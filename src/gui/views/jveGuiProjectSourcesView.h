

#ifndef JVEGUIPROJECTSOURCESVIEW_H
#define JVEGUIPROJECTSOURCESVIEW_H


#include <QWidget>
#include <QVBoxLayout>


#include "jveGuiProjectSourcesViewBar.h"
#include "jveGuiProjectSourcesViewArea.h"


#include <QString>


class jveGuiProjectSourcesView : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesView(QWidget *parent);
        virtual  ~jveGuiProjectSourcesView(void);
    private slots:
        void slotStateChanged(const int state);
        void slotResetView(void);
        void slotApplyItemsFilter(const QString &searchString);
    private:
        // members
        QVBoxLayout                  mp_layout;
        jveGuiProjectSourcesViewBar  mp_bar;
        jveGuiProjectSourcesViewArea mp_area;
};


#endif // JVEGUIPROJECTSOURCESVIEW_H


