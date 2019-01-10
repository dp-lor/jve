

#ifndef JVEGUIPROJECTSETTINGSVIEW_H
#define JVEGUIPROJECTSETTINGSVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>


#include "../elements/jveGuiForm.h"
#include "../elements/jveGuiTimeFramesSpinsGroup.h"


class QEvent;


class jveGuiProjectSettingsView : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiProjectSettingsView(QWidget *parent);
        virtual  ~jveGuiProjectSettingsView(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotStateChanged(const int state);
        void slotResetView(void);
        void slotSetRangeStart(const int rangeStart);
        void slotSetRangeEnd(const int rangeEnd);
    private:
        // appearance
        QVBoxLayout mp_layout;
        jveGuiForm  mp_form;
        // ranges
        QLabel                     mp_labelStart;
        jveGuiTimeFramesSpinsGroup mp_startSpinsGroup;
        QLabel                     mp_labelEnd;
        jveGuiTimeFramesSpinsGroup mp_endSpinsGroup;
        // video
        QLabel    mp_labelVideoSize;
        QComboBox mp_comboVideoSize;
        QLabel    mp_labelVideoFps;
        QComboBox mp_comboVideoFps;
        // audio
        QLabel    mp_labelAudioChannels;
        QComboBox mp_comboAudioChannels;
        QLabel    mp_labelAudioSampleRate;
        QComboBox mp_comboAudioSampleRate;
};


#endif // JVEGUIPROJECTSETTINGSVIEW_H


