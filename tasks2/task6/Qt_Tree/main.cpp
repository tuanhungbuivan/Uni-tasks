#include <QApplication>
#include <QTreeView>
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

        MainWindow window;
        window.show();

        return app.exec();
}
