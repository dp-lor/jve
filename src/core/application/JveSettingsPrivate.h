

#ifndef JVESETTINGSPRIVATE_H
#define JVESETTINGSPRIVATE_H


#include <QSettings>
#include <QMutex>


class JveSettingsPrivate : public QSettings
{
    Q_OBJECT
    public:
        explicit  JveSettingsPrivate(void);
        virtual  ~JveSettingsPrivate(void);
    public:
        void lock(void);
        void unlock(void);
    private:
        // members
        QMutex mp_mutex;
};


#endif // JVESETTINGSPRIVATE_H


