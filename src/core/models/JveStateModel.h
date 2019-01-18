

#ifndef JVESTATEMODEL_H
#define JVESTATEMODEL_H


#include "JveBaseModel.h"


class JveProject;


class JveStateModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveStateModel(JveProject *project, QDomElement domElement);
        virtual  ~JveStateModel(void);
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
        JveProject *mp_project;
        int         mp_playheadPosition;
        int         mp_videoMonitorQuality;
};


#endif // JVESTATEMODEL_H


