

#include "jveIdProviderPrivate.h"


#include <QDateTime>
#include <QCryptographicHash>


jveIdProviderPrivate jveIdProvider;


jveIdProviderPrivate::jveIdProviderPrivate(void)
    : mp_ids()
{
}

jveIdProviderPrivate::~jveIdProviderPrivate(void)
{
}

void
jveIdProviderPrivate::clear(void)
{
    mp_ids.clear();
}

bool
jveIdProviderPrivate::isExists(const QString &id) const
{
    return mp_ids.contains(id);
}

void
jveIdProviderPrivate::addExternal(const QString &id)
{
    mp_ids << QString(id);
}

QString
jveIdProviderPrivate::generate(void) const
{
    QString id;

    do {

        id = QCryptographicHash::hash(
            QDateTime::currentDateTime()
                .toString("yyyyMMddHHmmsszzz")
                .toUtf8(),
            QCryptographicHash::Md5
        ).toHex();

    } while (mp_ids.contains(id));

    return id;
}


