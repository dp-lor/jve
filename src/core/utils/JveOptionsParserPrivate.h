

#ifndef JVEOPTIONSPARSERPRIVATE_H
#define JVEOPTIONSPARSERPRIVATE_H


#include <QObject>
#include <QStringList>
#include <QString>
#include <QCommandLineParser>


class JveOptionsParserPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  JveOptionsParserPrivate(void);
        virtual  ~JveOptionsParserPrivate(void);
    public:
        void parse(
                const QStringList &arguments,
                const int          forcedOptions
        );
        int     options(void) const;
        QString projectFilePath(void) const;
    private:
        // members
        int                mp_options;
        QCommandLineParser mp_parser;
        QString            mp_projectFilePath;
};


#endif // JVEOPTIONSPARSERPRIVATE_H


