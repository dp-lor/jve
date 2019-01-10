

#ifndef JVEPROJECTSETTINGSSIGNALSPRIVATE_H
#define JVEPROJECTSETTINGSSIGNALSPRIVATE_H


#include <QObject>


class jveProjectSettingsSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveProjectSettingsSignalsPrivate(void);
        virtual  ~jveProjectSettingsSignalsPrivate(void);
    signals:
        void wantResetView(void);
        void wantSetRangeStart(const int rangeStart);
        void wantSetRangeEnd(const int rangeEnd);
        void rangeStartChanged(const int rangeStart);
        void rangeEndChanged(const int rangeEnd);
};


#endif // JVEPROJECTSETTINGSSIGNALSPRIVATE_H


