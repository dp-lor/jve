

#ifndef JVEPROJECTBASEMODEL_H
#define JVEPROJECTBASEMODEL_H


#include <QObject>
#include <QDomElement>
#include <QVector>


class JveBaseModel : public QObject
{
    Q_OBJECT
    public:
        explicit  JveBaseModel(QDomElement domElement);
        virtual  ~JveBaseModel(void);
    public:
        void deleteChild(JveBaseModel *child);
        void clear(void);
    public:
        JveBaseModel * removeChild(JveBaseModel *child);
        JveBaseModel * appendChild(JveBaseModel *child);
        JveBaseModel * attachChild(
                  JveBaseModel *child,
            const bool          appendMode = false
        );
    public:
        JveBaseModel * parent(void);
        int            level(void) const;
        JveBaseModel * previousSibling(void);
        JveBaseModel * nextSibling(void);
        JveBaseModel * child(JveBaseModel *maybeChild);
    public:
        void setParent(JveBaseModel *parent);
        void setLevel(const int level);
        void setPreviousSibling(JveBaseModel *sibling);
        void setNextSibling(JveBaseModel *sibling);
    public:
        void appendDomToNewParentDom(QDomElement parentDomElement);
        void removeDomFromParentDom(void);
    public:
        virtual void setUp(void);
        virtual void upSet(void);
    protected:
        // members
        QDomElement              mp_domElement;
        JveBaseModel            *mp_parent;
        int                      mp_level;
        JveBaseModel            *mp_previousSibling;
        JveBaseModel            *mp_nextSibling;
        QVector<JveBaseModel *>  mp_children;
};


#endif // JVEPROJECTBASEMODEL_H


