

#include "jveMessageHandler.h"


#include <QRegExp>


jveMessageHandler::jveMessageHandler(void)
    : QAbstractMessageHandler(Q_NULLPTR)
{
}

jveMessageHandler::~jveMessageHandler(void)
{
}

void
jveMessageHandler::handleMessage(
          QtMsgType        type,
    const QString         &description,
    const QUrl            &identifier,
    const QSourceLocation &sourceLocation
)
{
    Q_UNUSED(type);
    Q_UNUSED(identifier);

    mp_sourceLocation = sourceLocation;
    mp_statusMessage  = description;
}

int
jveMessageHandler::line(void) const
{
    return mp_sourceLocation.line();
}

int
jveMessageHandler::column(void) const
{
    return mp_sourceLocation.column();
}

QString
jveMessageHandler::statusMessage(void) const
{
    return mp_statusMessage;
}

QString
jveMessageHandler::statusMessageText(void) const
{
    return QString(mp_statusMessage).remove(QRegExp("<[^>]*>"));
}


