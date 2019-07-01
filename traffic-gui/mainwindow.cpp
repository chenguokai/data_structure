#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    initDatabase();
    initUI();
    initSlots();

}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::day_judger(std::string str) {
#define MAG 86400
    if (str == "Mon") return MAG * 1;
    else if (str == "Tue") return MAG * 2;
    else if (str == "Wed") return MAG * 3;
    else if (str == "Thu") return MAG * 4;
    else if (str == "Fri") return MAG * 5;
    else if (str == "Sat") return MAG * 6;
    else if (str == "Sun") return MAG * 7;
    else return -1;
#undef MAG
}

void MainWindow::initDatabase() {
    int hours,minutes,seconds;
    struct trans rec;
#define FILEPATH "/Users/cgk/Documents/CPP/data_structure/12306/merge/new.txt"
    freopen(FILEPATH,"r",stdin);
    std::ios::sync_with_stdio(false);
    int counts = 0;
    while (!(std::cin.eof())) {
        std::cout<<++counts<<"\n";
        std::cin>>rec.v_name>>rec.v_start>>rec.start_day>>rec.start_clock>>rec.v_end>>rec.end_day>>rec.end_clock>>rec.length_str>>rec.seat_type>>rec.price;

        if (rec.v_name[0] == 'C') {
            rec.v_type = 0;
        } else {
            rec.v_type = 1;
        }
        std::sscanf(rec.start_clock.c_str(),"%d:%d:%d",&hours,&minutes,&seconds);
        rec.start_time = day_judger(rec.start_day) + hours * 3600 + minutes * 60 + seconds;
        std::sscanf(rec.end_clock.c_str(),"%d:%d:%d",&hours,&minutes,&seconds);
        rec.end_time = day_judger(rec.end_day) + hours * 3600 + minutes * 60 + seconds;
        rec.length = rec.end_time - rec.start_time;
        if (rec.start_time < 0 || rec.end_time < 0) {
            // we have got a wrong data base
            std::cout<<"The database is corrupted!\n";
            std::exit(0);
        }
        cities.insert(rec.v_start);
        cities.insert(rec.v_end);
        v.push_back(rec);
    }

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
    search_city_log->setFixedHeight(250);
    search_city_log->setFixedWidth(200);
    search_city_log->setReadOnly(true);

    search_route_log = new QPlainTextEdit;
    search_route_log->setFixedHeight(250);
    //search_route_log->setFixedWidth(200);
    search_route_log->setReadOnly(true);


    add_city = new QPushButton;
    del_city = new QPushButton;
    add_route = new QPushButton;
    del_route = new QPushButton;

    add_city->setText("添加城市");
    del_city->setText("删除城市");
    add_route->setText("添加路线");
    del_route->setText("删除路线");
    search_city_input_view = new QHBoxLayout;
    search_route_input_view = new QHBoxLayout;

    search_city_input_view->addWidget(search_city);
    search_city_input = new QLineEdit;
    search_city_input->setFixedHeight(20);
    search_city_input->setFixedWidth(70);
    search_route_start_input = new QLineEdit;
    search_route_start_input->setFixedHeight(20);
    search_route_start_input->setFixedWidth(45);
    search_route_end_input = new QLineEdit;
    search_route_end_input->setFixedHeight(20);
    search_route_end_input->setFixedWidth(45);
    search_city_input_view->addWidget(search_city_input);


    search_route_start = new QLabel;
    search_route_start->setText("搜索路线 起点");

    search_route_end = new QLabel;
    search_route_end->setText("终点");

    search_route_num = new QLabel;
    search_route_num->setText("车次");

    search_route_num_input = new QLineEdit;
    search_route_num_input->setFixedHeight(20);
    search_route_num_input->setFixedWidth(45);





    search_route_input_view->addWidget(search_route_start);
    search_route_input_view->addWidget(search_route_start_input);
    search_route_input_view->addWidget(search_route_end);
    search_route_input_view->addWidget(search_route_end_input);
    search_route_input_view->addWidget(search_route_num);
    search_route_input_view->addWidget(search_route_num_input);

    search_city_edit = new QHBoxLayout;
    search_route_edit = new QHBoxLayout;

    search_city_edit->addWidget(add_city);
    search_city_edit->addWidget(del_city);

    search_route_edit->addWidget(add_route);
    search_route_edit->addWidget(del_route);

    right_city->addLayout(search_city_input_view);
    right_city->addWidget(search_city_log);
    right_city->addLayout(search_city_edit);

    right_route->addLayout(search_route_input_view);
    right_route->addWidget(search_route_log);
    right_route->addLayout(search_route_edit);
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
    std::set<std::string>::iterator i;
    for (i = cities.begin(); i != cities.end(); ++i ){
            from_station->addItem((QString)((*i).c_str()));
    }
    for (i = cities.begin(); i != cities.end(); ++i ){
            to_station->addItem((QString)((*i).c_str()));
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
    mode->addItem("最快到达");
    mode->addItem("最省钱到达");
    mode->addItem("中转最少到达");

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
    connect(kickstart,SIGNAL(clicked(bool)),this,SLOT(start_route()));
    connect(search_city_input,SIGNAL(returnPressed()),this,SLOT(start_city_search()));
    connect(search_route_start_input,SIGNAL(returnPressed()),this,SLOT(start_route_search()));
    connect(search_route_end_input,SIGNAL(returnPressed()),this,SLOT(start_route_search()));
    connect(search_route_num_input,SIGNAL(returnPressed()),this,SLOT(start_route_search()));
    connect(add_city,SIGNAL(clicked(bool)),this,SLOT(add_city_func()));
    connect(del_city,SIGNAL(clicked(bool)),this,SLOT(del_city_func()));
    connect(add_route,SIGNAL(clicked(bool)),this,SLOT(add_route_func()));
    connect(del_route,SIGNAL(clicked(bool)),this,SLOT(del_route_func()));
}
