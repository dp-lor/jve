

#ifndef JVEGUIMENUPROJECTSOURCES_H
#define JVEGUIMENUPROJECTSOURCES_H


#include <QMenu>


#include "../elements/jveGuiAction.h"


class QEvent;


class jveGuiMenuProjectSources : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuProjectSources(QWidget *parent);
        virtual  ~jveGuiMenuProjectSources(void);
    protected:
        void changeEvent(QEvent *event);
    public:
        void setTargetRow(const int row);
    private:
        void updateTranslations(void);
    signals:
        void wantViewItemProperties(const int targetRow);
        void wantRemoveItem(const int targetRow);
    private slots:
        void slotSetState(const int state);
        void slotActionPropertiesTriggered(void);
        void slotActionRemoveTriggered(void);
    public:
        // members
        jveGuiAction actionProperties;
        jveGuiAction actionRemove;
        jveGuiAction actionAddMediaItems;
        jveGuiAction actionAddImagesSequenceItem;
        jveGuiAction actionRemoveUnused;
    private:
        // members
        int mp_targetRow;
};


#endif // JVEGUIMENUPROJECTSOURCES_H


