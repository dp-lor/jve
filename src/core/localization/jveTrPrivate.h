

#ifndef JVETRPRIVATE_H
#define JVETRPRIVATE_H


#include <QObject>
#include <QString>
#include <QVector>


class jveTrPrivate : public QObject
{
    Q_OBJECT
    public:
        explicit  jveTrPrivate(void);
        virtual  ~jveTrPrivate(void);
    public:
        QString textAt(const int key) const;
        QString titleAt(const int type) const;
        QString messageAt(const int subType) const;
    public:
        void update(void);
    private:
        // members
        QVector<QString> mp_texts;
        QVector<QString> mp_titles;
        QVector<QString> mp_messages;
};


#endif // JVETRPRIVATE_H


