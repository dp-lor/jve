

#ifndef JVEGUISAVEPROJECTDIALOG_H
#define JVEGUISAVEPROJECTDIALOG_H


#include <QFileDialog>


class QEvent;


class jveGuiSaveProjectDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  jveGuiSaveProjectDialog(QWidget *parent);
        virtual  ~jveGuiSaveProjectDialog(void);
    public:
        QString getNormalizedFilePath(void) const;
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUISAVEPROJECTDIALOG_H


