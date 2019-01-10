

#include "jveGuiBlackStyle.h"


#include <QLabel>
#include <QSpinBox>


#include "../definitions/jveGuiBlackStyleDefines.h"


void
jveGuiBlackStyle::polish(QWidget *widget)
{
    // label
    if (QLabel *label = qobject_cast<QLabel *>(widget)) {

        label->setStyleSheet(
            "QLabel {"
                "color: "
                    JVE_GUI_BLACK_STYLE_TEXT_COLOR ";"
            "}"
            "QLabel:disabled {"
                "color: "
                    JVE_GUI_BLACK_STYLE_DISABLED_TEXT_COLOR ";"
            "}"
        );

    // spin box
    } else if (QSpinBox *spinBox = qobject_cast<QSpinBox *>(widget)) {
        spinBox->setStyleSheet(
            "QSpinBox {"
                "padding: 0.14em;"
                "color: "
                    JVE_GUI_BLACK_STYLE_TEXT_COLOR ";"
                "selection-color: "
                    JVE_GUI_BLACK_STYLE_TEXT_COLOR ";"
                "background-color: "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "selection-background-color: "
                    JVE_GUI_BLACK_STYLE_SELECTION_BACKGROUND_COLOR ";"
                "border: 1px solid "
                    JVE_GUI_BLACK_STYLE_BORDER_COLOR ";"
            "}"
            "QSpinBox:disabled {"
                "color: "
                    JVE_GUI_BLACK_STYLE_DISABLED_TEXT_COLOR ";"
            "}"
            "QSpinBox:up-button {"
                "subcontrol-origin: border;"
                "subcontrol-position: top right;"
                "background-color: transparent;"
                "border-left: 1px solid "
                    JVE_GUI_BLACK_STYLE_BORDER_COLOR ";"
            "}"
            "QSpinBox:down-button {"
                "subcontrol-origin: border;"
                "subcontrol-position: bottom right;"
                "background-color: transparent;"
                "border-left: 1px solid "
                    JVE_GUI_BLACK_STYLE_BORDER_COLOR ";"
            "}"
            "QSpinBox:up-arrow,"
            "QSpinBox::up-arrow:disabled,"
            "QSpinBox::up-arrow:off,"
            "QSpinBox::up-arrow:hover {"
                "width: 0px;"
                "height: 0px;"
                "border-top: 2px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "border-left: 5px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "border-right: 5px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "border-bottom: 6px solid "
                    JVE_GUI_BLACK_STYLE_BORDER_COLOR ";"
            "}"
            "QSpinBox:down-arrow,"
            "QSpinBox::down-arrow:disabled,"
            "QSpinBox::down-arrow:off,"
            "QSpinBox::down-arrow:hover {"
                "width: 0px;"
                "height: 0px;"
                "border-top: 6px solid "
                    JVE_GUI_BLACK_STYLE_BORDER_COLOR ";"
                "border-left: 5px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "border-right: 5px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
                "border-bottom: 2px solid "
                    JVE_GUI_BLACK_STYLE_BACKGROUND_COLOR ";"
            "}"
        );
    }
}


