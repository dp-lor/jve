

#ifndef JVEAVPRIVATE_H
#define JVEAVPRIVATE_H


#include <QMap>


class JveAVPrivate
{
    public:
        explicit  JveAVPrivate(void);
        virtual  ~JveAVPrivate(void);
    public:
        QMap<QString, const char *> & getProjectSettingsVideoSizes(void);
    private:
        void buildProjectSettingsVideoSizes(void);
    private:
        // members
        QMap<QString, const char *> mp_projectSettingsVideoSizes;
};


#endif // JVEAVPRIVATE_H


