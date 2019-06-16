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

    open_file_des = new QLabel;
    open_file_des->setText("数据文件：");
    path = new QLineEdit;
    path->setPlaceholderText("数据文件路径");
    path->setFixedHeight(18);

    file_view = new QHBoxLayout;
    file_view->addWidget(open_file_des);
    file_view->addWidget(path);

    sort1_des = new QLabel;
    sort1_des->setText("排序参数1");
    sort2_des = new QLabel;
    sort2_des->setText("排序参数2");
    sort3_des = new QLabel;
    sort3_des->setText("排序参数3");
    sort4_des = new QLabel;
    sort4_des->setText("排序参数4");
    sort5_des = new QLabel;
    sort5_des->setText("排序参数5");
    sort1_input = new QComboBox;
    sort2_input = new QComboBox;
    sort3_input = new QComboBox;
    sort4_input = new QComboBox;
    sort5_input = new QComboBox;
    sort1_input->setFixedWidth(70);
    sort2_input->setFixedWidth(70);
    sort3_input->setFixedWidth(70);
    sort4_input->setFixedWidth(70);
    sort5_input->setFixedWidth(70);
    sort1_input_list = new QListWidget;
    sort2_input_list = new QListWidget;
    sort3_input_list = new QListWidget;
    sort4_input_list = new QListWidget;
    sort5_input_list = new QListWidget;

    sort1_input->setModel(sort1_input_list->model());
    sort2_input->setModel(sort2_input_list->model());
    sort3_input->setModel(sort3_input_list->model());
    sort4_input->setModel(sort4_input_list->model());
    sort5_input->setModel(sort5_input_list->model());


    sort_input_view = new QHBoxLayout;
    sort_input_view->addWidget(sort1_des);
    sort_input_view->addWidget(sort1_input);
    sort_input_view->addWidget(sort2_des);
    sort_input_view->addWidget(sort2_input);
    sort_input_view->addWidget(sort3_des);
    sort_input_view->addWidget(sort3_input);
    sort_input_view->addWidget(sort4_des);
    sort_input_view->addWidget(sort4_input);
    sort_input_view->addWidget(sort5_des);
    sort_input_view->addWidget(sort5_input);

    res = new QPlainTextEdit;
    res->setReadOnly(true);
    name_view = new QHBoxLayout;
    name_included = new QCheckBox;
    name_included->setText("首项是否为名称");
    name_view->addWidget(name_included);
    kickstart = new QPushButton;
    kickstart->setText("开始排序");
    name_view->addWidget(kickstart);
    name_view->setAlignment(Qt::AlignRight);

    main_view = new QVBoxLayout;
    main_view->addLayout(file_view);
    main_view->addLayout(sort_input_view);
    main_view->addWidget(res);
    main_view->addLayout(name_view);



    auto central = new QWidget;
    central->setLayout(main_view);
    setCentralWidget(central);

}
void MainWindow::initSlots() {

}
