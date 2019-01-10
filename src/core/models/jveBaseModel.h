

#ifndef JVEPROJECTBASEMODEL_H
#define JVEPROJECTBASEMODEL_H


#include <QObject>
#include <QDomElement>
#include <QVector>


class jveApplication;


class jveBaseModel : public QObject
{
    Q_OBJECT
    public:
        explicit jveBaseModel(
            jveApplication *app,
            QDomElement     domNode
        );
        virtual ~jveBaseModel(void);
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
        jveBaseModel * child(jveBaseModel *maybeChild);
        jveBaseModel * previousSibling(void);
        jveBaseModel * nextSibling(void);
        int            level(void) const;
    public:
        void setParent(jveBaseModel *parent);
        void setPreviousSibling(jveBaseModel *sibling);
        void setNextSibling(jveBaseModel *sibling);
        void setLevel(const int level);
        void appendDomNodeToNewParentDomNode(QDomElement parentDomNode);
        void removeDomNodeFromParentDomNode(void);
    public:
        virtual void setUp(void);
        virtual void upSet(void);
    protected:
        // members
        jveApplication          *mp_app;
        jveBaseModel            *mp_parent;
        jveBaseModel            *mp_previousSibling;
        jveBaseModel            *mp_nextSibling;
        int                      mp_level;
        QVector<jveBaseModel *>  mp_children;
        QDomElement              mp_domNode;
};


#endif // JVEPROJECTBASEMODEL_H


