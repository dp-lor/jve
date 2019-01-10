

#include "jveBaseModel.h"
#include "../application/jveApplication.h"


jveBaseModel::jveBaseModel(
    jveApplication *app,
    QDomElement     domNode
) : QObject(Q_NULLPTR),
        mp_app(app),
        mp_parent(Q_NULLPTR),
        mp_previousSibling(Q_NULLPTR),
        mp_nextSibling(Q_NULLPTR),
        mp_level(0),
        mp_children(),
        mp_domNode(domNode)
{
}

jveBaseModel::~jveBaseModel(void)
{
}

void
jveBaseModel::deleteChild(jveBaseModel *child)
{
    child->clear();
    child->upSet();

    delete removeChild(child);
}

void
jveBaseModel::clear(void)
{
    QVector<jveBaseModel *> children(mp_children);

    while (!children.isEmpty()) {
        deleteChild(children.takeLast());
    }
}

jveBaseModel *
jveBaseModel::removeChild(jveBaseModel *child)
{
    int childIndex = mp_children.lastIndexOf(child);

    if (-1 < childIndex) {

        int previousIndex = childIndex - 1;
        int nextIndex     = childIndex + 1;

        jveBaseModel *previousSibling = (-1 < previousIndex)
                ? mp_children.at(previousIndex)
                : Q_NULLPTR;
        jveBaseModel *nextSibling = (mp_children.size() > nextIndex)
                ? mp_children.at(nextIndex)
                : Q_NULLPTR;

        if (Q_NULLPTR != previousSibling) {
            previousSibling->setNextSibling(nextSibling);
        }
        if (Q_NULLPTR != nextSibling) {
            nextSibling->setPreviousSibling(previousSibling);
        }

        mp_children.removeAt(childIndex);
        child->setParent(Q_NULLPTR);
        child->setPreviousSibling(Q_NULLPTR);
        child->setNextSibling(Q_NULLPTR);
        child->removeDomNodeFromParentDomNode();

    }

    return child;
}

jveBaseModel *
jveBaseModel::appendChild(jveBaseModel *child)
{
    return attachChild(child, true);
}

jveBaseModel *
jveBaseModel::attachChild(
          jveBaseModel *child,
    const bool          appendMode
)
{
    jveBaseModel *previousSibling = Q_NULLPTR;

    child->setParent(this);
    if (mp_children.size()) {
        previousSibling = mp_children.last();
        previousSibling->setNextSibling(child);
    }
    child->setPreviousSibling(previousSibling);
    child->setNextSibling(Q_NULLPTR);
    mp_children.append(child);
    if (appendMode) {
        child->appendDomNodeToNewParentDomNode(mp_domNode);
    }

    return child;
}

jveBaseModel *
jveBaseModel::parent(void)
{
    return mp_parent;
}

jveBaseModel *
jveBaseModel::child(jveBaseModel *maybeChild)
{
    int childIndex = mp_children.lastIndexOf(maybeChild);

    return (-1 < childIndex)
        ? mp_children.at(childIndex)
        : Q_NULLPTR;
}

jveBaseModel *
jveBaseModel::previousSibling(void)
{
    return mp_previousSibling;
}

jveBaseModel *
jveBaseModel::nextSibling(void)
{
    return mp_nextSibling;
}

int
jveBaseModel::level(void) const
{
    return mp_level;
}

void
jveBaseModel::setParent(jveBaseModel *parent)
{
    mp_parent = parent;

    setLevel(Q_NULLPTR != mp_parent ? (mp_parent->level() + 1) : 0);
}

void
jveBaseModel::setPreviousSibling(jveBaseModel *sibling)
{
    mp_previousSibling = sibling;
}

void
jveBaseModel::setNextSibling(jveBaseModel *sibling)
{
    mp_nextSibling = sibling;
}

void
jveBaseModel::setLevel(const int level)
{
    mp_level = level;

    for (int i = 0; i < mp_children.size(); i += 1) {
        mp_children.at(i)->setLevel(mp_level + 1);
    }
}

void
jveBaseModel::appendDomNodeToNewParentDomNode(QDomElement parentDomNode)
{
    mp_domNode = parentDomNode.appendChild(mp_domNode).toElement();
}

void
jveBaseModel::removeDomNodeFromParentDomNode(void)
{
    mp_domNode = mp_domNode.parentNode().removeChild(mp_domNode).toElement();
}

void
jveBaseModel::setUp(void)
{
}

void
jveBaseModel::upSet(void)
{
}


