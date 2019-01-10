

#ifndef JVESETTINGSPRIVATE_H
#define JVESETTINGSPRIVATE_H


#include <QSettings>
#include <QMutex>


class jveSettingsPrivate : public QSettings
{
    Q_OBJECT
    public:
        explicit  jveSettingsPrivate(void);
        virtual  ~jveSettingsPrivate(void);
    public:
        void lock(void);
        void unlock(void);
    private:
        // members
        QMutex mp_mutex;
};


#endif // JVESETTINGSPRIVATE_H


