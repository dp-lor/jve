

#ifndef JVEGUIMENULANGUAGE_H
#define JVEGUIMENULANGUAGE_H


#include <QMenu>
#include <QEvent>
#include <QString>
#include <QActionGroup>


#include "../elements/jveGuiAction.h"


class jveGuiMenuLanguage : public QMenu
{
    Q_OBJECT
    public:
        explicit  jveGuiMenuLanguage(QWidget *parent);
        virtual  ~jveGuiMenuLanguage(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void setUpLocaleAction(
                  QAction *action,
            const QString &locale
        );
        void updateLocaleActionState(
                  QAction *action,
            const QString &locale
        );
        void updateTranslations(void);
    private slots:
        void slotLocaleChanged(const QString &locale);
        void slotCatchSetLocale(QAction *action);
    public:
        // members
        QActionGroup localeActionsGroup;
        jveGuiAction actionEnUs;
        jveGuiAction actionRuRu;
        jveGuiAction actionReset;
};


#endif // JVEGUIMENULANGUAGE_H


