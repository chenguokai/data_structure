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
    QLabel *search_route_start, *search_route_end;
    QPlainTextEdit* search_city_log;
    QPlainTextEdit* search_route_log;
    QPushButton *add_city, *del_city, *add_route, *del_route;


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
