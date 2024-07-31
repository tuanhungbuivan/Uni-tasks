#include "tree.h"

Tree::Tree(const QString &name)
    : m_name(name)
    , m_parent(nullptr)
{
}

Tree::~Tree()
{
    qDeleteAll(m_children);
}

Tree *Tree::createChild(const QString &name)
{

    Tree *child = new Tree(name);
    child->m_parent = this;
    m_children.append(child);
    return child;

}

void Tree::removeChild(Tree *child)
{
    m_children.removeOne(child);
    child->m_parent = nullptr;
    delete child;
}

QList<Tree*> Tree::children() const
{
    return m_children;
}

void Tree::addChild(Tree *child)
{
    this->children().append(child);

}

QString Tree::name() const
{
    return m_name;
}

void Tree::setName(const QString &name)
{
    m_name = name;
}

Tree *Tree::parent() const
{
    return m_parent;
}
