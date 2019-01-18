

#include "JveGuiPreferencesDialog.h"
#include "../../core/definitions/JveDefines.h"


JveGuiPreferencesDialog::JveGuiPreferencesDialog(QWidget *parent)
    : QDialog(parent)
{
    // properties
    setWindowModality(Qt::ApplicationModal);
    setMinimumSize(600, 600);

    setWindowTitle(JVE_NAME_STRING);

    // layout
    mp_layout = new QVBoxLayout(this);
    mp_layout->setContentsMargins(10, 10, 10, 10);
    // main tabs widget
    mp_mainTabs = new QTabWidget(this);
    mp_layout->addWidget(mp_mainTabs);

    // add tabs
    mp_mainTabs->addTab(new QWidget, QObject::tr("General"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Resources"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Appearance"));
    mp_mainTabs->addTab(new QWidget, QObject::tr("Other"));
}

JveGuiPreferencesDialog::~JveGuiPreferencesDialog(void)
{
    delete mp_mainTabs;
    delete mp_layout;
}


