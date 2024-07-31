/********************************************************************************
** Form generated from reading UI file 'tree.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TREE_H
#define UI_TREE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tree
{
public:

    void setupUi(QWidget *Tree)
    {
        if (Tree->objectName().isEmpty())
            Tree->setObjectName(QString::fromUtf8("Tree"));
        Tree->resize(400, 300);

        retranslateUi(Tree);

        QMetaObject::connectSlotsByName(Tree);
    } // setupUi

    void retranslateUi(QWidget *Tree)
    {
        Tree->setWindowTitle(QCoreApplication::translate("Tree", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tree: public Ui_Tree {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREE_H
