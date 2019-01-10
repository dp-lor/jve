

#ifndef JVEPROJECTSTATE_H
#define JVEPROJECTSTATE_H


#include "jveBaseModel.h"


class jveProjectState : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProjectState(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectState(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        int playheadPosition(void) const;
    public:
        void setPlayheadPosition(
            const int  position,
            const bool locked = false
        );
        void setVideoMonitorQuality(
            const int  quality,
            const bool locked = false
        );
    private slots:
        void slotSetPlayheadPosition(const int position);
        void slotSetVideoMonitorQuality(const int quality);
    private:
        // members
        int mp_playheadPosition;
        int mp_videoMonitorQuality;
};


#endif // JVEPROJECTSTATE_H


