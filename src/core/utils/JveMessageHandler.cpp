

#include "JveMessageHandler.h"


#include <QRegExp>


JveMessageHandler::JveMessageHandler(void)
    : QAbstractMessageHandler(nullptr)
{
}

JveMessageHandler::~JveMessageHandler(void)
{
}

void
JveMessageHandler::handleMessage(
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
JveMessageHandler::line(void) const
{
    return mp_sourceLocation.line();
}

int
JveMessageHandler::column(void) const
{
    return mp_sourceLocation.column();
}

QString
JveMessageHandler::statusMessage(void) const
{
    return mp_statusMessage;
}

QString
JveMessageHandler::statusMessageText(void) const
{
    return QString(mp_statusMessage).remove(QRegExp("<[^>]*>"));
}


