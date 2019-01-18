

#ifndef JVEGUIREPORTBOX_H
#define JVEGUIREPORTBOX_H


#include <QMessageBox>


#include "../../core/application/JveReport.h"


class JveGuiReportBox : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  JveGuiReportBox(QWidget *parent);
        virtual  ~JveGuiReportBox(void);
    public:
        void exec(const JveReport &report);
};


#endif // JVEGUIREPORTBOX_H


