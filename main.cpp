#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QApplication>
#include "his.hpp"

//using namespace his;



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
