

#ifndef JVEMESSAGEHANDLER_H
#define JVEMESSAGEHANDLER_H


#include <QAbstractMessageHandler>


class jveMessageHandler : public QAbstractMessageHandler
{
    Q_OBJECT
    public:
        explicit  jveMessageHandler(void);
        virtual  ~jveMessageHandler(void);
    protected:
        virtual void handleMessage(
                  QtMsgType        type,
            const QString         &description,
            const QUrl            &identifier,
            const QSourceLocation &sourceLocation
        );
    public:
        int     line(void) const;
        int     column(void) const;
        QString statusMessage(void) const;
        QString statusMessageText(void) const;
    private:
        // members
        QSourceLocation mp_sourceLocation;
        QString         mp_statusMessage;
};


#endif // JVEMESSAGEHANDLER_H


