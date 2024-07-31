#ifndef TREE_H
#define TREE_H

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QDataStream>
#include <QStringList>

class Tree
{
public:
    Tree(const QString &name);
    ~Tree();

    QString name() const;
    void setName(const QString &name);

    Tree *parent() const;
    void setParent(Tree *parent);

    void addChild(Tree *child);
    Tree *createChild(const QString &name);
    QList<Tree*> children() const;

    void removeChild(Tree *child);




private:
    QString m_name;
    Tree *m_parent;
    QList<Tree*> m_children;
};

#endif // TREE_H
