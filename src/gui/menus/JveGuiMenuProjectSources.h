

#ifndef JVEGUIMENUPROJECTSOURCES_H
#define JVEGUIMENUPROJECTSOURCES_H


#include <QMenu>


#include "../elements/JveGuiAction.h"


class QEvent;


class JveGuiMenuProjectSources : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuProjectSources(QWidget *parent);
        virtual  ~JveGuiMenuProjectSources(void);
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
        JveGuiAction actionProperties;
        JveGuiAction actionRemove;
        JveGuiAction actionAddMediaItems;
        JveGuiAction actionAddImagesSequenceItem;
        JveGuiAction actionRemoveUnused;
    private:
        // members
        int mp_targetRow;
};


#endif // JVEGUIMENUPROJECTSOURCES_H


