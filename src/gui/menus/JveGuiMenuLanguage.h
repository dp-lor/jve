

#ifndef JVEGUIMENULANGUAGE_H
#define JVEGUIMENULANGUAGE_H


#include <QMenu>
#include <QEvent>
#include <QString>
#include <QActionGroup>


#include "../elements/JveGuiAction.h"


class JveGuiMenuLanguage : public QMenu
{
    Q_OBJECT
    public:
        explicit  JveGuiMenuLanguage(QWidget *parent);
        virtual  ~JveGuiMenuLanguage(void);
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
        JveGuiAction actionEnUs;
        JveGuiAction actionRuRu;
        JveGuiAction actionReset;
};


#endif // JVEGUIMENULANGUAGE_H


