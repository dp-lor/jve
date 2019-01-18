

#ifndef JVEPROJECTBASEMODEL_H
#define JVEPROJECTBASEMODEL_H


#include <QObject>
#include <QDomElement>
#include <QVector>


class jveBaseModel : public QObject
{
    Q_OBJECT
    public:
        explicit  jveBaseModel(QDomElement domElement);
        virtual  ~jveBaseModel(void);
    public:
        void deleteChild(jveBaseModel *child);
        void clear(void);
    public:
        jveBaseModel * removeChild(jveBaseModel *child);
        jveBaseModel * appendChild(jveBaseModel *child);
        jveBaseModel * attachChild(
                  jveBaseModel *child,
            const bool          appendMode = false
        );
    public:
        jveBaseModel * parent(void);
        int            level(void) const;
        jveBaseModel * previousSibling(void);
        jveBaseModel * nextSibling(void);
        jveBaseModel * child(jveBaseModel *maybeChild);
    public:
        void setParent(jveBaseModel *parent);
        void setLevel(const int level);
        void setPreviousSibling(jveBaseModel *sibling);
        void setNextSibling(jveBaseModel *sibling);
    public:
        void appendDomToNewParentDom(QDomElement parentDomElement);
        void removeDomFromParentDom(void);
    public:
        virtual void setUp(void);
        virtual void upSet(void);
    protected:
        // members
        QDomElement              mp_domElement;
        jveBaseModel            *mp_parent;
        int                      mp_level;
        jveBaseModel            *mp_previousSibling;
        jveBaseModel            *mp_nextSibling;
        QVector<jveBaseModel *>  mp_children;
};


#endif // JVEPROJECTBASEMODEL_H


