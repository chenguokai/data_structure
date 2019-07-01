#include "mainwindow.h"
#include <QApplication>
std::vector<trans>v;
std::set<std::string>cities;
std::string start_stat,end_stat,train_no_str,start_time_str,end_time_str,price_str;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
