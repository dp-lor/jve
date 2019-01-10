

#ifndef JVEPROJECTSTATESIGNALSPRIVATE_H
#define JVEPROJECTSTATESIGNALSPRIVATE_H


#include <QObject>


class jveProjectStateSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveProjectStateSignalsPrivate(void);
        virtual  ~jveProjectStateSignalsPrivate(void);
    signals:
        void wantResetView(void);
        void playheadPositionChanged(const int playheadPosition);
        void videoMonitorQualityChanged(const int quality);
        void wantSetPlayheadPosition(const int playheadPosition);
        void wantSetVideoMonitorQuality(const int quality);
};


#endif // JVEPROJECTSTATESIGNALSPRIVATE_H


