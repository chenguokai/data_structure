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

struct trans{
    int v_type;
    /*
     * type 0: flight (actually C trains)
     * type 1: trains (actually non-C trains)
    */
    std::string v_name;
    std::string v_start;
    std::string v_end;
    std::string start_day;
    std::string end_day;
    std::string start_clock;
    std::string end_clock;
    int start_time;
    int end_time;
    int length;
    std::string length_str;
    std::string seat_type;
    double price;

    /* K6735 乌鲁木齐 Mon 13:28:00 石河子 Mon 14:53:00 1:25:00 硬座 21.5 */
};
extern std::vector<trans>v;
extern std::set<std::string>cities;
extern std::string start_stat,end_stat,train_no_str,start_time_str,end_time_str,price_str;

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
