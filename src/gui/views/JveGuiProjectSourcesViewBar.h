

#ifndef JVEGUIPROJECTSOURCESVIEWBAR_H
#define JVEGUIPROJECTSOURCESVIEWBAR_H


#include <QWidget>
#include <QHBoxLayout>


#include "../elements/JveGuiSearchWidget.h"
#include "../elements/JveGuiToolButton.h"


class QEvent;


class JveGuiProjectSourcesViewBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSourcesViewBar(QWidget *parent);
        virtual  ~JveGuiProjectSourcesViewBar(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    public:
        // members
        JveGuiSearchWidget searchWidget;
    private:
        // members
        QHBoxLayout        mp_layout;
        JveGuiToolButton   mp_buttonAddMediaItems;
        JveGuiToolButton   mp_buttonAddImagesSequenceItem;
};


#endif // JVEGUIPROJECTSOURCESVIEWBAR_H


