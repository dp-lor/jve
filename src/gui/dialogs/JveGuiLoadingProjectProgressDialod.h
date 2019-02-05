

#ifndef JVEGUILOADINGPROJECTPROGRESSDIALOG_H
#define JVEGUILOADINGPROJECTPROGRESSDIALOG_H


#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QHBoxLayout>


#include "../elements/JveGuiButton.h"


class QEvent;


class JveGuiLoadingProjectProgressDialod : public QDialog
{
    Q_OBJECT
    public:
        explicit  JveGuiLoadingProjectProgressDialod(QWidget *parent);
        virtual  ~JveGuiLoadingProjectProgressDialod(void);
    protected:
        void changeEvent(QEvent *event);
    private slots:
        void slotProgressUpdated(const int value);
    private:
        void updateTranslations(void);
    private:
        // members
        QVBoxLayout  mp_layout;
        QLabel       mp_title;
        QProgressBar mp_progress;
        QLabel       mp_description;
        QWidget      mp_buttonsWrapper;
        QHBoxLayout  mp_buttonsLayout;
        JveGuiButton mp_cancelButton;
};


#endif // JVEGUILOADINGPROJECTPROGRESSDIALOG_H


