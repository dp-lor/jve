

#ifndef JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H
#define JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H


#include <QFileDialog>


class QEvent;


class JveGuiAddProjectSourcesImagesSequenceItemDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit JveGuiAddProjectSourcesImagesSequenceItemDialog(
            QWidget *parent
        );
        virtual ~JveGuiAddProjectSourcesImagesSequenceItemDialog(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUIADDPROJECTSOURCESIMAGESSEQUENCEITEMDIALOG_H


