#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    initUI();
    initSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_right() {
    right_city = new QVBoxLayout;

    right_route = new QVBoxLayout;
    right_view->addLayout(right_city);
    right_view->addStretch(3);
    right_view->addLayout(right_route);
    search_city = new QLabel;
    search_city->setText("搜索城市");
    search_route = new QLabel;
    search_route->setText("搜索路线");

    search_city_log = new QPlainTextEdit;
    search_city_log->setFixedHeight(200);
    search_city_log->setReadOnly(true);

    search_route_log = new QPlainTextEdit;
    search_route_log->setFixedHeight(200);
    search_route_log->setReadOnly(true);


    add_city = new QPushButton;
    del_city = new QPushButton;
    add_route = new QPushButton;
    del_route = new QPushButton;

    add_city->setText("添加城市");
    del_city->setText("删除城市");
    add_route->setText("添加路线");
    del_route->setText("删除路线");

    right_city->addWidget(search_city);
    right_city->addWidget(search_city_log);
    right_route->addWidget(search_route);
    right_route->addWidget(search_route_log);
}

void MainWindow::initUI() {
    from_station = new QComboBox;
    to_station = new QComboBox;
    from_station->setEditable(true);
    to_station->setEditable(true);
    from_list = new QListWidget;
    to_list = new QListWidget;
    from_station->setModel(from_list->model());
    to_station->setModel(to_list->model());
    from_station->setView(from_list);
    to_station->setView(to_list);
    for (int i = 0; i < 5; ++i)
        {
            from_station->addItem("item " + QString::number(i));
        }
    inputview = new QHBoxLayout;
    from_des = new QLabel;
    to_des = new QLabel;
    from_des->setText("出发地");
    to_des->setText("目的地");

    inputview->addWidget(from_des);
    inputview->addWidget(from_station);
    inputview->addWidget(to_des);
    inputview->addWidget(to_station);

    mainview = new QVBoxLayout;

    mode_des = new QLabel;
    mode_des->setText("选择策略");
    mode = new QComboBox;
    mode_list = new QListWidget;
    mode->setModel(mode_list->model());
    mode->setView(mode_list);

    modeview = new QHBoxLayout;
    modeview->addWidget(mode_des);
    modeview->addWidget(mode);

    result = new QPlainTextEdit();
    result->setFixedHeight(200);
    result->setReadOnly(true);
    result->setPlainText("This is a test string");

    kickstart = new QPushButton;
    kickstart->setText("开始寻路");
    kickview = new QHBoxLayout;
    kickview->addSpacing(100);
    kickview->addWidget(kickstart);

    mainview->addLayout(inputview);
    mainview->addLayout(modeview);
    mainview->addWidget(result);
    mainview->addLayout(kickview);


    right_view = new QHBoxLayout;
    init_right();

    real_mainview = new QHBoxLayout;
    real_mainview->addLayout(mainview);
    real_mainview->addStretch(1);
    real_mainview->addLayout(right_view);




    auto central = new QWidget;
    central->setLayout(real_mainview);
    setCentralWidget(central);
}

void MainWindow::initSlots() {

}
