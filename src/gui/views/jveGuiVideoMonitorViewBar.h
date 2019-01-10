

#ifndef JVEGUIVIDEOMONITORVIEWBAR_H
#define JVEGUIVIDEOMONITORVIEWBAR_H


#include <QWidget>
#include <QHBoxLayout>


//#include "../elements/jveGuiToolButton.h"
#include "../elements/jveGuiLabelSpinBoxGroup.h"
#include "../elements/jveGuiTwoLabelsGroup.h"


class QEvent;


class jveGuiVideoMonitorViewBar : public QWidget
{
    Q_OBJECT
    public:
        explicit  jveGuiVideoMonitorViewBar(QWidget *parent);
        virtual  ~jveGuiVideoMonitorViewBar(void);
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
        //jveGuiToolButton        mp_heightHolder;
        jveGuiLabelSpinBoxGroup mp_qualityGroup;
        jveGuiTwoLabelsGroup    mp_fpsGroup;
};


#endif // JVEGUIVIDEOMONITORVIEWBAR_H


