

#ifndef JVEPROJECTSTATESIGNALSPRIVATE_H
#define JVEPROJECTSTATESIGNALSPRIVATE_H


#include <QObject>


class JveProjectStateSignalsPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  JveProjectStateSignalsPrivate(void);
        virtual  ~JveProjectStateSignalsPrivate(void);
    signals:
        void wantResetView(void);
        void playheadPositionChanged(const int playheadPosition);
        void videoMonitorQualityChanged(const int quality);
        void wantSetPlayheadPosition(const int playheadPosition);
        void wantSetVideoMonitorQuality(const int quality);
};


#endif // JVEPROJECTSTATESIGNALSPRIVATE_H


