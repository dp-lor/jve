

#ifndef JVEGUITRANSPORTBAR_H
#define JVEGUITRANSPORTBAR_H


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>


#include "../elements/jveGuiToolButton.h"
#include "../elements/jveGuiToolSpacer.h"
#include "../elements/jveGuiTimeFramesSpinsGroup.h"


class QEvent;


class jveGuiTransportBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiTransportBar(QWidget *parent);
        virtual  ~jveGuiTransportBar(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotSetState(const int state);
        void slotResetView(void);
        void slotSetPlayheadPosition(const int position);
    private:
        // members
        QHBoxLayout                mp_layout;
        jveGuiToolButton           mp_buttonSeekToStart;
        jveGuiToolButton           mp_buttonSeekToPrevKF;
        jveGuiToolButton           mp_buttonPlayPause;
        jveGuiToolButton           mp_buttonSeekToNextKF;
        jveGuiToolButton           mp_buttonSeekToEnd;
        jveGuiToolButton           mp_buttonLoop;
        jveGuiToolSpacer           mp_spacer;
        jveGuiTimeFramesSpinsGroup mp_playheadPositionSpinsGroup;
};


#endif // JVEGUITRANSPORTBAR_H


