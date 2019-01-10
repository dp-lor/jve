

#ifndef JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H
#define JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H


#include <QFileDialog>


class QEvent;


class jveGuiAddProjectSourcesImagesSequenceItemDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit jveGuiAddProjectSourcesImagesSequenceItemDialog(
            QWidget *parent
        );
        virtual ~jveGuiAddProjectSourcesImagesSequenceItemDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H


