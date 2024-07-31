#include "mainwindow.h"
#include "tree.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QSaveFile>
#include <QInputDialog>
#include <QModelIndexList>
#include <QStack>
#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    treeView = new QTreeView;
    model = new QStandardItemModel;
    treeView->setModel(model);

    // Tworzy root i dodaje do root kolejne dzieci
    root = new Tree("Root");
    Tree *child1 = root->createChild("Child 1");
    Tree *child2 = root->createChild("Child 2");
    child1->createChild("Child 1-1");
    child1->createChild("Child 1-2");
    child2->createChild("Child 2-1");
    child2->createChild("Child 2-2");
    buildModel(root, model->invisibleRootItem());

    // Tworzenie Gui
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(treeView);
    QPushButton *addButton = new QPushButton("Add");
    layout->addWidget(addButton);
    QPushButton *removeButton = new QPushButton("Remove");
    layout->addWidget(removeButton);
    QPushButton *moveButton = new QPushButton("Move");
    layout->addWidget(moveButton);
    QPushButton *saveButton = new QPushButton("Save");
    layout->addWidget(saveButton);
    QPushButton *readButton = new QPushButton("Read");
    layout->addWidget(readButton);

    // Polaczenie buttons do odpowiednich przyciskow
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addItem);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::removeItem);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveToFile);
    connect(readButton, &QPushButton::clicked, this, &MainWindow::readFromFile);
    connect(moveButton, &QPushButton::clicked, this, &MainWindow::moveItem);
    setLayout(layout);
}


MainWindow::~MainWindow()
{

}

void MainWindow::buildModel(Tree *tree, QStandardItem *parent)
{
    // Dodanie nazwy drzewa do modelu
    QStandardItem *item = new QStandardItem(tree->name());
    parent->appendRow(item);

    // dodawanie nazwy dzieci do modelu
    foreach (Tree *child, tree->children())
    buildModel(child, item);
}

void MainWindow::addItem()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Item", "Enter name:", QLineEdit::Normal, QString(), &ok);
    if (!ok || name.isEmpty()){
        return;
    }

    // Pobiera zaznaczony index gdzie mamy wstawic nowy element
    QModelIndex index = treeView->currentIndex();
    Tree *parentTree = getTreeFromIndex(index);
    if (!parentTree){
        parentTree = root;
    }

    // Tworzy nowe drzewo i dodaje to drzewa i modelu drzewa
    Tree *newTree = parentTree->createChild(name);
    QStandardItem *newItem = new QStandardItem(name);
    model->itemFromIndex(index)->appendRow(newItem);
}


Tree* MainWindow::getTreeFromIndex(const QModelIndex &index)
{
    if (!index.isValid()){
        return nullptr;
    }
    QStandardItem *item = model->itemFromIndex(index);
    Tree *tree = root;
    while (item && tree) {
        int row = item->row();
        if (row >= tree->children().size()){
            return nullptr;
        }
        tree = tree->children()[row];
        item = item->parent();
    }
    return tree;
}


void MainWindow::removeItem()
{
    // Usuwa wybrany pozycja
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid()){
        return;
    }
    // Usuwa pozycje z modelu
    QStandardItem *item = model->itemFromIndex(index);
    QStandardItem *parent = item->parent();
    if (!parent){
        parent = model->invisibleRootItem();
    }
    parent->removeRow(item->row());
}

void MainWindow::moveItem() {
    // Get the source and destination indices
    QModelIndex sourceIndex = treeView->currentIndex();
    QModelIndex destinationIndex = getDestinationIndex();
    if (!sourceIndex.isValid() || !destinationIndex.isValid()) {
        return;
    }

    // Get the source and destination items
    QStandardItem *sourceItem = model->itemFromIndex(sourceIndex);
    QStandardItem *destinationItem = model->itemFromIndex(destinationIndex);
    if (!sourceItem || !destinationItem) {
        return;
    }

    // Remove the source item from its current location
    int sourceRow = sourceIndex.row();
    int sourceCol = sourceIndex.column();
    sourceItem->parent()->removeRow(sourceRow);

    // Insert the source item at the destination location
    int destinationRow = destinationIndex.row();
    destinationItem->insertRow(destinationRow, sourceItem);

    // update tree data
    // update tree data
    Tree *sourceTree = getTreeFromIndex(sourceIndex);
    Tree *destinationTree = getTreeFromIndex(destinationIndex);

    sourceTree->parent()->removeChild(sourceTree);
    destinationTree->addChild(sourceTree);

}


QModelIndex MainWindow::getDestinationIndex()
{
    // Show a dialog to get the destination item name
    bool ok;
    QString destinationName = QInputDialog::getText(this, "Move Item", "Enter destination name:", QLineEdit::Normal, QString(), &ok);
    if (!ok || destinationName.isEmpty())
    {
        return QModelIndex();
    }

    // Search the model for the destination item
    QList<QStandardItem*> items = model->findItems(destinationName);
    if (items.isEmpty())
    {
        QMessageBox::warning(this, "Move Item", "Cannot find destination item.");
        return QModelIndex();
    }

    // Return the index of the first item found
    return model->indexFromItem(items.first());
}




void MainWindow::saveToFile()
{
    //Zapisuje kontent z TreeView do pliku
    QString fileName = QFileDialog::getSaveFileName(this, "Save Tree", QString(), "Text Files (*.txt)");
    if (fileName.isEmpty()){
        return;
    }
    //Otwiera plik do pisania
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    QMessageBox::critical(this, "Error", "Failed to save tree: " + file.errorString());
        return;
    }

    //Zapisuje drzewa do pliku
    QTextStream stream(&file);
    saveTree(root, file, 0);

    file.close();
}

void MainWindow::saveTree(Tree *tree,QFile &file,int depth)
{
    //Zapis do pliku
    QTextStream stream(&file);
    QString prefix;
    for (int i = 0; i < depth; ++i) {
        prefix += " ";
    }

    stream << prefix << tree->name() << Qt::endl;

    foreach (Tree *child, tree->children()) {
        saveTree(child, file, depth + 1);
    }

}

void MainWindow::readFromFile()
{
    //Usuwanie obecnego modelu
    model->clear();

    //Otwiera filedialog aby wybrac plik
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QString(), "Text Files (*.txt)");
    if (fileName.isEmpty()){
        return;
    }
    //Otwiera plik i odczytuje dane
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream stream(&file);
    QStack<QStandardItem*> parentStack;
    parentStack.push(model->invisibleRootItem());

    while (!stream.atEnd())
    {
        //Wczytuje linie z pliku
        QString line = stream.readLine();

        // Sprawdza ilosc spacji, co bedzie wyznaczac poziom np rodzica dziecka
        int depth = 0;
        while (line[depth] == ' '){
            ++depth;
        }
        line = line.mid(depth);

        // zdejmuje z stacku jezeli obecja glebokosc jest mniejsza od poprzedniego
        while (parentStack.size() > depth + 1){
            parentStack.pop();
        }
        // Tworzy nowy przedmiot dla obecnej linijki i dodaje do modelu
        QStandardItem *item = new QStandardItem(line);
        parentStack.top()->appendRow(item);
        parentStack.push(item);
    }

    file.close();
}




