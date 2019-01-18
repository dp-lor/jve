

#include "JveReport.h"


#include "../mutexes/JveLocalizationMutex.h"
#include "../localization/JveTr.h"


JveReport::JveReport(void)
    : mp_forced(false)
{
}

JveReport::JveReport(const int type, const int subType)
    : mp_forced(false)
{
    fill(type, subType);
}

JveReport::JveReport(const int type, const int subType, const QString &arg1)
    : mp_forced(false)
{
    fill(type, subType, arg1);
}

JveReport::JveReport(
    const int      type,
    const int      subType,
    const QString &arg1,
    const QString &arg2
) : mp_forced(false)
{
    fill(type, subType, arg1, arg2);
}

JveReport::~JveReport(void)
{
}

void
JveReport::fill(const int type, const int subType)
{
    mp_type    = type;
    mp_subType = subType;

    JveLocalizationMutex.lock();

    mp_title   = JveTr.titleAt(type);
    mp_message = JveTr.messageAt(subType);

    JveLocalizationMutex.unlock();
}

void
JveReport::fill(const int type, const int subType, const QString &arg1)
{
    mp_type    = type;
    mp_subType = subType;

    JveLocalizationMutex.lock();

    mp_title   = JveTr.titleAt(type);
    mp_message = JveTr.messageAt(subType).arg(arg1);

    JveLocalizationMutex.unlock();
}

void
JveReport::fill(
    const int      type,
    const int      subType,
    const QString &arg1,
    const QString &arg2
)
{
    mp_type    = type;
    mp_subType = subType;

    JveLocalizationMutex.lock();

    mp_title   = JveTr.titleAt(type);
    mp_message = JveTr.messageAt(subType).arg(arg1).arg(arg2);

    JveLocalizationMutex.unlock();
}

void
JveReport::setForced(const bool forced)
{
    mp_forced = forced;
}

int
JveReport::type(void) const
{
    return mp_type;
}

int
JveReport::subType(void) const
{
    return mp_subType;
}

bool
JveReport::isForced(void) const
{
    return mp_forced;
}

QString
JveReport::title(void) const
{
    return mp_title;
}

QString
JveReport::message(void) const
{
    return mp_message;
}


