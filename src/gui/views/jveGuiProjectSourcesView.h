

#ifndef JVEGUIPROJECTSOURCESVIEW_H
#define JVEGUIPROJECTSOURCESVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QString>


#include "jveGuiProjectSourcesViewBar.h"
#include "jveGuiProjectSourcesViewArea.h"


class QEvent;


class jveGuiProjectSourcesView : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesView(QWidget *parent);
        virtual  ~jveGuiProjectSourcesView(void);
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
        jveGuiProjectSourcesViewBar  mp_bar;
        jveGuiProjectSourcesViewArea mp_area;
};


#endif // JVEGUIPROJECTSOURCESVIEW_H


