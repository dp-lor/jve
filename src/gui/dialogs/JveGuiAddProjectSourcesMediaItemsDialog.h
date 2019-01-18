

#ifndef JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H
#define JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H


#include <QFileDialog>


class QEvent;


class JveGuiAddProjectSourcesMediaItemsDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiAddProjectSourcesMediaItemsDialog(QWidget *parent);
        virtual  ~JveGuiAddProjectSourcesMediaItemsDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIADDPROJECTSOURCESMEDIAITEMSDIALOG_H


