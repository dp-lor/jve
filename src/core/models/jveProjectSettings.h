

#ifndef JVEPROJECTSETTINGS_H
#define JVEPROJECTSETTINGS_H


#include "jveBaseModel.h"


class jveProjectSettings : public jveBaseModel
{
    Q_OBJECT
    public:
        explicit jveProjectSettings(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveProjectSettings(void);
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


#endif // JVEPROJECTSETTINGS_H


