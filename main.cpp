#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
