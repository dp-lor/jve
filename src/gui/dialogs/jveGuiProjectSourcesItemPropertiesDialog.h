

#ifndef JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H
#define JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>


#include "../../core/structures/jveProjectSourcesItemStruct.h"

#include "../elements/jveGuiButton.h"


class QEvent;


class jveGuiProjectSourcesItemPropertiesDialog : public QDialog
{
    Q_OBJECT
    public:
        explicit jveGuiProjectSourcesItemPropertiesDialog(
                  QWidget                     *parent,
            const jveProjectSourcesItemStruct &item
        );
        virtual ~jveGuiProjectSourcesItemPropertiesDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private:
        // members
        jveProjectSourcesItemStruct mp_item;
    private:
        // members
        QVBoxLayout  mp_layout;
        QWidget      mp_buttonsBox;
        QHBoxLayout  mp_buttonsBoxLayout;
        jveGuiButton mp_btnSave;
        jveGuiButton mp_btnClose;
};


#endif // JVEGUIPROJECTSOURCESITEMPROPERTIESDIALOG_H


