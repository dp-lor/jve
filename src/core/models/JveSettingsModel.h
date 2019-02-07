

#ifndef JVESETTINGSMODEL_H
#define JVESETTINGSMODEL_H


#include "JveBaseModel.h"


class JveSettingsModel : public JveBaseModel
{
    Q_OBJECT
    public:
        explicit  JveSettingsModel(QDomElement domElement);
        virtual  ~JveSettingsModel(void);
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
        int mp_rangeStart;
        int mp_rangeEnd;
};


#endif // JVESETTINGSMODEL_H


