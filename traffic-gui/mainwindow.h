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



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
