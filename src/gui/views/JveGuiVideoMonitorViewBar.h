

#ifndef JVEGUIVIDEOMONITORVIEWBAR_H
#define JVEGUIVIDEOMONITORVIEWBAR_H


#include <QWidget>
#include <QHBoxLayout>


//#include "../elements/JveGuiToolButton.h"
#include "../elements/JveGuiLabelSpinBoxGroup.h"
#include "../elements/JveGuiTwoLabelsGroup.h"


class QEvent;


class JveGuiVideoMonitorViewBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  JveGuiVideoMonitorViewBar(QWidget *parent);
        virtual  ~JveGuiVideoMonitorViewBar(void);
    protected:
        void changeEvent(QEvent *event);
    private:
        void updateTranslations(void);
    private slots:
        void slotResetView(void);
        void slotSetVideoMonitorQuality(const int quality);
    private:
        // members
        QHBoxLayout             mp_layout;
        //JveGuiToolButton        mp_heightHolder;
        JveGuiLabelSpinBoxGroup mp_qualityGroup;
        JveGuiTwoLabelsGroup    mp_fpsGroup;
};


#endif // JVEGUIVIDEOMONITORVIEWBAR_H


