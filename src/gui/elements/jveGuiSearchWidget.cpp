

#include "jveGuiSearchWidget.h"


#include <QEvent>
#include <QFontMetrics>


#include "../definitions/jveGuiAppearanceDefines.h"
#include "../definitions/jveGuiMediaDefines.h"


jveGuiSearchWidget::jveGuiSearchWidget(QWidget *parent)
    : QWidget(parent),
        searchInput(this),
        mp_layout(this),
        mp_searchIcon(this, JVE_GUI_ICON_SEARCH)
{
    // properties
    setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );

    // layout
    mp_layout.setMargin(0);
    mp_layout.setSpacing(0);
    mp_layout.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    // search icon
    mp_searchIcon.setStyleSheet("border: none;");
    mp_searchIcon.setEnabled(false);
    mp_layout.addWidget(&mp_searchIcon);

    // search input
    searchInput.setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );
    searchInput.setMinimumWidth(
        searchInput.fontMetrics().maxWidth()
            * JVE_GUI_SEARCH_WIDGET_MIN_VISIBLE_CHARACTERS
    );
    searchInput.setClearButtonEnabled(true);
    mp_layout.addWidget(&searchInput);
}

jveGuiSearchWidget::~jveGuiSearchWidget(void)
{
}


