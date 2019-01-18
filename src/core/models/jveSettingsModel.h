

#ifndef JVESETTINGSMODEL_H
#define JVESETTINGSMODEL_H


#include "jveBaseModel.h"


class jveProject;


class jveSettingsModel : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveSettingsModel(
            jveProject  *project,
            QDomElement  domElement
        );
        virtual ~jveSettingsModel(void);
    public:
        void setUp(void);
        void upSet(void);
    public:
        int rangeStart(void) const;
        int rangeEnd(void) const;
    public:
        void setRangeStart(const int rangeStart, const bool locked = false);
        void setRangeEnd(const int rangeEnd, const bool locked = false);
    private slots:
        void slotSetRangeStart(const int rangeStart);
        void slotSetRangeEnd(const int rangeEnd);
    private:
        // members
        jveProject *mp_project;
        int         mp_rangeStart;
        int         mp_rangeEnd;
};


#endif // JVESETTINGSMODEL_H


