

#include "jveReport.h"


#include "../mutexes/jveLocalizationMutex.h"
#include "../localization/jveTr.h"


jveReport::jveReport(void)
    : mp_forced(false)
{
}

jveReport::jveReport(const int type, const int subType)
    : mp_forced(false)
{
    fill(type, subType);
}

jveReport::jveReport(const int type, const int subType, const QString &arg1)
    : mp_forced(false)
{
    fill(type, subType, arg1);
}

jveReport::jveReport(
    const int      type,
    const int      subType,
    const QString &arg1,
    const QString &arg2
) : mp_forced(false)
{
    fill(type, subType, arg1, arg2);
}

jveReport::~jveReport(void)
{
}

void
jveReport::fill(const int type, const int subType)
{
    mp_type    = type;
    mp_subType = subType;

    jveLocalizationMutex.lock();

    mp_title   = jveTr.titleAt(type);
    mp_message = jveTr.messageAt(subType);

    jveLocalizationMutex.unlock();
}

void
jveReport::fill(const int type, const int subType, const QString &arg1)
{
    mp_type    = type;
    mp_subType = subType;

    jveLocalizationMutex.lock();

    mp_title   = jveTr.titleAt(type);
    mp_message = jveTr.messageAt(subType).arg(arg1);

    jveLocalizationMutex.unlock();
}

void
jveReport::fill(
    const int      type,
    const int      subType,
    const QString &arg1,
    const QString &arg2
)
{
    mp_type    = type;
    mp_subType = subType;

    jveLocalizationMutex.lock();

    mp_title   = jveTr.titleAt(type);
    mp_message = jveTr.messageAt(subType).arg(arg1).arg(arg2);

    jveLocalizationMutex.unlock();
}

void
jveReport::setForced(const bool forced)
{
    mp_forced = forced;
}

int
jveReport::type(void) const
{
    return mp_type;
}

int
jveReport::subType(void) const
{
    return mp_subType;
}

bool
jveReport::isForced(void) const
{
    return mp_forced;
}

QString
jveReport::title(void) const
{
    return mp_title;
}

QString
jveReport::message(void) const
{
    return mp_message;
}


