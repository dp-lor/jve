

#ifndef JVEGUIREPORTBOX_H
#define JVEGUIREPORTBOX_H


#include <QMessageBox>


#include "../../core/application/jveReport.h"


class jveGuiReportBox : public QMessageBox
{
    Q_OBJECT
    public:
        explicit  jveGuiReportBox(QWidget *parent);
        virtual  ~jveGuiReportBox(void);
    public:
        void exec(const jveReport &report);
};


#endif // JVEGUIREPORTBOX_H


