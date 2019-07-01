#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QComboBox>
#include <QWidgetList>
#include <QListWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
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
    QLabel* open_file_des;
    QPushButton *open_file_button;
    QFileDialog* open_file_dialog;
    QAction *file_open_action;
    QLabel* sort1_des;
    QLabel* sort2_des;
    QLabel* sort3_des;
    QLabel* sort4_des;
    QLabel* sort5_des;
    QComboBox* sort1_input;
    QComboBox* sort2_input;
    QComboBox* sort3_input;
    QComboBox* sort4_input;
    QComboBox* sort5_input;
    QListWidget* sort1_input_list;
    QListWidget* sort2_input_list;
    QListWidget* sort3_input_list;
    QListWidget* sort4_input_list;
    QListWidget* sort5_input_list;
    QCheckBox* name_included;
    //QLabel* name_included_des;
    QPlainTextEdit* res;
    QLineEdit* path;
    QHBoxLayout* file_view;
    QHBoxLayout* sort_input_view;
    QHBoxLayout* name_view;
    QVBoxLayout* main_view;
    QPushButton* kickstart;
public slots:
    void start_sort();
    void open_file_choose();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
