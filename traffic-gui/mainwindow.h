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
