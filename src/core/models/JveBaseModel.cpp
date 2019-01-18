

#include "JveBaseModel.h"


JveBaseModel::JveBaseModel(QDomElement domElement)
    : QObject(nullptr),
        mp_domElement(domElement),
        mp_parent(nullptr),
        mp_level(0),
        mp_previousSibling(nullptr),
        mp_nextSibling(nullptr),
        mp_children()
{
}

JveBaseModel::~JveBaseModel(void)
{
}

void
JveBaseModel::deleteChild(JveBaseModel *child)
{
    child->clear();
    child->upSet();

    delete removeChild(child);
}

void
JveBaseModel::clear(void)
{
    QVector<JveBaseModel *> children(mp_children);

    while (!children.isEmpty()) {
        deleteChild(children.takeLast());
    }
}

JveBaseModel *
JveBaseModel::removeChild(JveBaseModel *child)
{
    int childIndex = mp_children.lastIndexOf(child);

    if (-1 < childIndex) {

        int previousIndex = childIndex - 1;
        int nextIndex     = childIndex + 1;

        JveBaseModel *previousSibling = (-1 < previousIndex)
                ? mp_children.at(previousIndex)
                : nullptr;
        JveBaseModel *nextSibling = (mp_children.size() > nextIndex)
                ? mp_children.at(nextIndex)
                : nullptr;

        if (nullptr != previousSibling) {
            previousSibling->setNextSibling(nextSibling);
        }
        if (nullptr != nextSibling) {
            nextSibling->setPreviousSibling(previousSibling);
        }

        mp_children.removeAt(childIndex);
        child->setParent(nullptr);
        child->setPreviousSibling(nullptr);
        child->setNextSibling(nullptr);
        child->removeDomFromParentDom();

    }

    return child;
}

JveBaseModel *
JveBaseModel::appendChild(JveBaseModel *child)
{
    return attachChild(child, true);
}

JveBaseModel *
JveBaseModel::attachChild(
          JveBaseModel *child,
    const bool          appendMode
)
{
    JveBaseModel *previousSibling = nullptr;

    child->setParent(this);
    if (mp_children.size()) {
        previousSibling = mp_children.last();
        previousSibling->setNextSibling(child);
    }
    child->setPreviousSibling(previousSibling);
    child->setNextSibling(nullptr);
    mp_children.append(child);
    if (appendMode) {
        child->appendDomToNewParentDom(mp_domElement);
    }

    return child;
}

JveBaseModel *
JveBaseModel::parent(void)
{
    return mp_parent;
}

int
JveBaseModel::level(void) const
{
    return mp_level;
}

JveBaseModel *
JveBaseModel::previousSibling(void)
{
    return mp_previousSibling;
}

JveBaseModel *
JveBaseModel::nextSibling(void)
{
    return mp_nextSibling;
}

JveBaseModel *
JveBaseModel::child(JveBaseModel *maybeChild)
{
    int childIndex = mp_children.lastIndexOf(maybeChild);

    return (-1 < childIndex)
        ? mp_children.at(childIndex)
        : nullptr;
}

void
JveBaseModel::setParent(JveBaseModel *parent)
{
    mp_parent = parent;

    setLevel(nullptr != mp_parent ? (mp_parent->level() + 1) : 0);
}

void
JveBaseModel::setLevel(const int level)
{
    mp_level = level;

    for (int i = 0; i < mp_children.size(); i++) {
        mp_children.at(i)->setLevel(mp_level + 1);
    }
}

void
JveBaseModel::setPreviousSibling(JveBaseModel *sibling)
{
    mp_previousSibling = sibling;
}

void
JveBaseModel::setNextSibling(JveBaseModel *sibling)
{
    mp_nextSibling = sibling;
}

void
JveBaseModel::appendDomToNewParentDom(QDomElement parentDomElement)
{
    mp_domElement = parentDomElement.appendChild(mp_domElement).toElement();
}

void
JveBaseModel::removeDomFromParentDom(void)
{
    mp_domElement
        = mp_domElement.parentNode().removeChild(mp_domElement).toElement();
}

void
JveBaseModel::setUp(void)
{
}

void
JveBaseModel::upSet(void)
{
}


