

#ifndef JVEGUISAVEPROJECTDIALOG_H
#define JVEGUISAVEPROJECTDIALOG_H


#include <QFileDialog>


class QEvent;


class JveGuiSaveProjectDialog : public QFileDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiSaveProjectDialog(QWidget *parent);
        virtual  ~JveGuiSaveProjectDialog(void);
    public:
        QString getNormalizedFilePath(void) const;
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
};


#endif // JVEGUISAVEPROJECTDIALOG_H


