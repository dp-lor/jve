

#ifndef JVEGUIPROJECTSETTINGSVIEW_H
#define JVEGUIPROJECTSETTINGSVIEW_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>


#include "../elements/JveGuiForm.h"
#include "../elements/JveGuiTimeFramesSpinsGroup.h"


class QEvent;


class JveGuiProjectSettingsView : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiProjectSettingsView(QWidget *parent);
        virtual  ~JveGuiProjectSettingsView(void);
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
        JveGuiForm  mp_form;
        // ranges
        QLabel                     mp_labelStart;
        JveGuiTimeFramesSpinsGroup mp_startSpinsGroup;
        QLabel                     mp_labelEnd;
        JveGuiTimeFramesSpinsGroup mp_endSpinsGroup;
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


