

#include "JveIdProviderPrivate.h"


#include <QDateTime>
#include <QCryptographicHash>


JveIdProviderPrivate JveIdProvider;


JveIdProviderPrivate::JveIdProviderPrivate(void)
    : mp_ids()
{
}

JveIdProviderPrivate::~JveIdProviderPrivate(void)
{
}

void
JveIdProviderPrivate::clear(void)
{
    mp_ids.clear();
}

bool
JveIdProviderPrivate::isExists(const QString &id) const
{
    return mp_ids.contains(id);
}

void
JveIdProviderPrivate::addExternal(const QString &id)
{
    mp_ids << QString(id);
}

QString
JveIdProviderPrivate::generate(void) const
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


