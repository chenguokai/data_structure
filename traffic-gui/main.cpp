#include "mainwindow.h"
#include <QApplication>
std::vector<trans>v;
std::set<std::string>cities;
std::string start_stat,end_stat,train_no_str,start_time_str,end_time_str,price_str;
int city_counts = 0;
std::map<std::string,int>m;
std::vector<node>edge[40000];
double dis[40000];
std::set<std::pair<int,int> >s;
bool ins[1010];
int pre[40000];
int pre_node[40000];
int reach_time[40000];
std::stack<trans>stk;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
