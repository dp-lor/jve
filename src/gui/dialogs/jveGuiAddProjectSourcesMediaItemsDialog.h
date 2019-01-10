

#ifndef JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H
#define JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H


#include <QFileDialog>


class QEvent;


class jveGuiAddProjectSourcesMediaItemsDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  jveGuiAddProjectSourcesMediaItemsDialog(QWidget *parent);
        virtual  ~jveGuiAddProjectSourcesMediaItemsDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H


