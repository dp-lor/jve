

#include "jveGuiReportBox.h"


#include <QList>
#include <QGridLayout>
#include <QSpacerItem>


#include "../../core/definitions/jveDefines.h"
#include "../definitions/jveGuiWindowsAppearanceDefines.h"


jveGuiReportBox::jveGuiReportBox(QWidget *parent)
    : QMessageBox(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setTextFormat(Qt::RichText);
    setWindowTitle(JVE_NAME_STRING);

    // ok button
    setStandardButtons(QMessageBox::Ok);
    setDefaultButton(QMessageBox::Ok);
}

jveGuiReportBox::~jveGuiReportBox(void)
{
}

void
jveGuiReportBox::exec(const jveReport &report)
{
    // icon
    switch (report.type()) {
        case jveReport::Error:
            setIcon(QMessageBox::Critical);
        break;
        case jveReport::Warning:
            setIcon(QMessageBox::Warning);
        break;
        // jveReport::Info
        // jveReport::Success
        default:
            setIcon(QMessageBox::Information);
        break;
    }

    // text
    if (jveReport::Error == report.type()) {
        setText(
            QString("<h4>%1 %2</h4>")
                .arg(report.title())
                .arg(report.subType(), 3, 10, QChar('0'))
        );
    } else {
        setText(QString("<h4>%1</h4>").arg(report.title()));
    }

    // informative text
    setInformativeText(report.message());

    // fix layout size
    QList<QGridLayout *> layouts = findChildren<QGridLayout *>();
    if (layouts.size()) {
        // bottom spacer
        QSpacerItem *bottomSpacer = new QSpacerItem(
            JVE_GUI_REPORT_BOX_MIN_WIDTH,
            0,
            QSizePolicy::Minimum,
            QSizePolicy::Fixed
        );
        // fix layout
        QGridLayout *layout = layouts[0];
        layout->addItem(
            bottomSpacer,
            layout->rowCount(),
            0,
            1,
            layout->columnCount()
        );
    }

    // execute box
    QMessageBox::exec();
}


