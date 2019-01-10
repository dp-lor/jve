

#ifndef JVEGUIPROJECTSOURCESVIEWBAR_H
#define JVEGUIPROJECTSOURCESVIEWBAR_H


#include <QWidget>
#include <QHBoxLayout>


#include "../elements/jveGuiSearchWidget.h"
#include "../elements/jveGuiToolButton.h"


class QEvent;


class jveGuiProjectSourcesViewBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSourcesViewBar(QWidget *parent);
        virtual  ~jveGuiProjectSourcesViewBar(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    public:
        // members
        jveGuiSearchWidget searchWidget;
    private:
        // members
        QHBoxLayout        mp_layout;
        jveGuiToolButton   mp_buttonAddMediaItems;
        jveGuiToolButton   mp_buttonAddImagesSequenceItem;
};


#endif // JVEGUIPROJECTSOURCESVIEWBAR_H


