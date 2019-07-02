#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QListWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <set>
#include <map>
#include <stack>

struct trans{
    int v_type;
    /*
     * type 0: flight (actually C trains)
     * type 1: trains (actually non-C trains)
    */
    std::string v_name;
    /*
     * the train's name in string
    */
    std::string v_start;
    /*
     * the name of the start station
    */
    std::string v_end;
    /*
     * the name of the end station
    */
    std::string start_day;
    /*
     * the day of setting off, in string
    */
    std::string end_day;
    /*
     * the day of arrival, in string
    */
    std::string start_clock;
    /*
     * the time of setting off, in string
    */
    std::string end_clock;
    /*
     * the time of arrival
    */
    int start_time; // the start time in integer
    int end_time;   // the end time in integer
    int length;     // the length of the train/flight
    std::string length_str; // the length of the train/flight in string
    std::string seat_type;  // the type of seat, in string
    double price;           // the price of the train/flight

    /*
     * sample input format:
     * K6735 乌鲁木齐 Mon 13:28:00 石河子 Mon 14:53:00 1:25:00 硬座 21.5
    */
};
struct node {
    /*
     * node is designed for storing the edges in our graph.
     * we need to store the destination and the departure point for Dijkstra to work
     * the offset stores where the edge came from in vector, so we can find
     * info that are not included in this struct
    */
    int to; // the destination
    int offset;
    int beg;
    double len; // the path's length

};
extern std::vector<trans>v; // the vector for all the trains available
extern std::set<std::string>cities; // the set of different cities
extern std::string start_stat,end_stat,train_no_str,start_time_str,end_time_str,price_str;
extern int city_counts;             // the total city count
extern std::map<std::string,int>m;  // make connections between cities' name and the node number
extern std::vector<node>edge[40000];// adjacent lists
extern std::set<std::pair<int,int> >s; // map between cities and their numbers
extern double dis[40000];           // distance for Dijkstra's Algorithm
extern bool ins[1010];              // judge whether one node is in the STL set / heap
extern int pre[40000];              // to reach the best path, we need the previous choice
extern int pre_node[40000];         // we need the node information to get the whole picture
extern std::stack<trans>stk;        // store the plan in order to output
extern int reach_time[40000];       // current we can reach one city at ...

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUI();
    void init_right();
    void initSlots();
    void initDatabase();
    int day_judger(std::string str);
    int city_mode; // the button's function
    int route_mode; // the button's function
#define ADD_OP 1
#define DEL_OP 2
    QComboBox* from_station;
    QComboBox* to_station;
    QComboBox* mode;
    QListWidget* from_list;
    QListWidget* to_list;
    QListWidget* mode_list;
    QLabel *from_des,*to_des,*mode_des;
    QHBoxLayout* inputview;
    QVBoxLayout* mainview;
    QHBoxLayout* modeview;
    QPlainTextEdit* result;
    QPushButton* kickstart;
    QHBoxLayout* kickview;
    QHBoxLayout* real_mainview;
    QHBoxLayout* right_view;
    QVBoxLayout* right_city;
    QVBoxLayout* right_route;
    QLabel* search_city;
    QLabel* search_route;
    QLabel *search_route_start, *search_route_end, *search_route_num;
    QPlainTextEdit* search_city_log;
    QPlainTextEdit* search_route_log;
    QPushButton *add_city, *del_city, *add_route, *del_route;
    QLineEdit* search_city_input;
    QLineEdit* search_route_start_input;
    QLineEdit* search_route_end_input;
    QLineEdit* search_route_num_input;
    QHBoxLayout* search_city_input_view;
    QHBoxLayout* search_route_input_view;
    QHBoxLayout* search_city_edit;
    QHBoxLayout* search_route_edit;
private slots:
    void start_route();
    void add_city_func();
    void del_city_func();
    void start_city_search();
    void start_route_search();
    void add_route_func();
    void del_route_func();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
