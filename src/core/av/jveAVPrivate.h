

#ifndef JVEAVPRIVATE_H
#define JVEAVPRIVATE_H


#include <QMap>


class jveAVPrivate
{
    public:
        explicit  jveAVPrivate(void);
        virtual  ~jveAVPrivate(void);
    public:
        QMap<QString, const char *> & getProjectSettingsVideoSizes(void);
    private:
        void buildProjectSettingsVideoSizes(void);
    private:
        // members
        QMap<QString, const char *> mp_projectSettingsVideoSizes;
};


#endif // JVEAVPRIVATE_H


