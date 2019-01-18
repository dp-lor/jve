

#include "JveGuiReportBox.h"


#include <QList>
#include <QGridLayout>
#include <QSpacerItem>


#include "../../core/definitions/JveDefines.h"
#include "../definitions/JveGuiWindowsAppearanceDefines.h"


JveGuiReportBox::JveGuiReportBox(QWidget *parent)
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

JveGuiReportBox::~JveGuiReportBox(void)
{
}

void
JveGuiReportBox::exec(const JveReport &report)
{
    // icon
    switch (report.type()) {
        case JveReport::Error:
            setIcon(QMessageBox::Critical);
        break;
        case JveReport::Warning:
            setIcon(QMessageBox::Warning);
        break;
        // JveReport::Info
        // JveReport::Success
        default:
            setIcon(QMessageBox::Information);
        break;
    }

    // text
    if (JveReport::Error == report.type()) {
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


