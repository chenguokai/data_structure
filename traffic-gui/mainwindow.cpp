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
    auto central = new QWidget;
    central->setLayout(mainview);
    setCentralWidget(central);
}

void MainWindow::initSlots() {

}
