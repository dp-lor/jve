

#ifndef JVEIDPROVIDERPRIVATE_H
#define JVEIDPROVIDERPRIVATE_H


#include <QString>
#include <QStringList>


class JveIdProviderPrivate
{
    public:
        explicit  JveIdProviderPrivate(void);
        virtual  ~JveIdProviderPrivate(void);
    public:
        void clear(void);
        bool isExists(const QString &id) const;
        void addExternal(const QString &id);
    public:
        QString generate(void) const;
    private:
        // members
        QStringList mp_ids;
};


#endif // JVEIDPROVIDERPRIVATE_H


