

#ifndef JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H
#define JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "../../core/structures/JveSourcesItemStruct.h"

#include "../elements/JveGuiButton.h"


class QEvent;


class JveGuiProjectSourcesItemPropertiesDialog : public QDialog
{
    Q_OBJECT
    public:
        explicit JveGuiProjectSourcesItemPropertiesDialog(
                  QWidget              *parent,
            const JveSourcesItemStruct &item
        );
        virtual ~JveGuiProjectSourcesItemPropertiesDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        JveSourcesItemStruct mp_item;
    private:
        // members
        QVBoxLayout  mp_layout;
        QWidget      mp_buttonsBox;
        QHBoxLayout  mp_buttonsBoxLayout;
        JveGuiButton mp_btnSave;
        JveGuiButton mp_btnClose;
};


#endif // JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H


