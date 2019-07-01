#include "mainwindow.h"
void MainWindow::start_route() {
    result->setPlainText("Successfully push!");

}
void MainWindow::add_city_func() {
    if (add_city->text() == "添加城市") {
        add_city->setText("确认");
        del_city->setText("取消");
        search_city_log->setPlainText("请确认添加的城市为"+search_city_input->text());
        search_city_log->setReadOnly(true);
        city_mode = ADD_OP;
    } else {

        // we confirmed the operation
        // todo: add the city
        add_city->setText("添加城市");
        del_city->setText("删除城市");
        search_city_log->setReadOnly(false);
        if (city_mode == ADD_OP) {
            search_city_log->setPlainText("添加城市 "+search_city_input->text()+"成功");
            cities.insert(search_city_input->text().toStdString());
        } else if (city_mode == DEL_OP) {
            search_city_log->setPlainText("删除城市 成功");
            cities.erase(search_city_input->text().toStdString());
            for (int i=0;i<v.size();++i) {
                if (v[i].v_start == search_city_input->text().toStdString() || v[i].v_end == search_city_input->text().toStdString()) {
                    v.erase(v.begin()+i);
                    --i; // balance automatic ++i
                }
            }
        }

    }
}
void MainWindow::del_city_func() {
    if (del_city->text() == "删除城市") {
        add_city->setText("确认");
        del_city->setText("取消");
        search_city_log->setPlainText("请确认删除的城市为"+search_city_input->text());
        search_city_log->setReadOnly(true);
        city_mode = DEL_OP;
    } else {
        // we canceled the operation
        add_city->setText("添加城市");
        del_city->setText("删除城市");
        search_city_log->setReadOnly(false);
        search_city_log->setPlainText("操作取消");
    }
}
void MainWindow::start_city_search() {
    QString log = "开始搜索\n";
    search_city_log->setPlainText(log);
    if (cities.find(search_city_input->text().toStdString()) != cities.end()) {
        log = log + "查找成功，找到" + search_city_input->text() + "\n";
    } else {
        log = log + "查找失败，" + search_city_input->text() + "未找到\n";
    }
    search_city_log->setPlainText(log);

}
void MainWindow::start_route_search() {
    QString log = "开始搜索";
    search_route_log->setPlainText(log);
    std::string from_city,to_city,train_no;
    from_city = search_route_start_input->text().toStdString();
    to_city = search_route_end_input->text().toStdString();
    train_no = search_route_num_input->text().toStdString();
    for (int i = 0;i < v.size();++i) {
        if (from_city == "" || v[i].v_start == from_city) {
            if (to_city == "" || v[i].v_end == to_city) {
                if (train_no == "" || v[i].v_name == train_no) {
                    log = log + "搜索到车次" + v[i].v_name.c_str() + ",发车日期 " + v[i].start_day.c_str() + "," + v[i].v_start.c_str() + "始发," + v[i].v_end.c_str() + "终到\n";
                }
            }
        }
    }
    log += "\n搜索完毕";
    search_route_log->setPlainText(log);

}
void MainWindow::add_route_func() {
    if (add_route->text() == "添加路线") {
        search_route_start->setText("发车时间");
        search_route_end->setText("到达时间");
        search_route_num->setText("票价");
        route_mode = ADD_OP;
        add_route->setText("确认");
        del_route->setText("取消");
        search_route_log->setPlainText("确认添加");

        start_stat = search_route_start_input->text().toStdString();
        end_stat = search_route_end_input->text().toStdString();
        train_no_str = search_route_num_input->text().toStdString();
        search_city_log->setReadOnly(true);

    } else {
        // confirm the operationn
        if (route_mode == ADD_OP) {
            QString log = "添加中\n";
            search_route_log->setPlainText(log);
            // input format
            start_time_str = search_route_start_input->text().toStdString();
            end_time_str = search_route_end_input->text().toStdString();
            price_str = search_route_num_input->text().toStdString();
            struct trans tmp;
            tmp.v_start = start_stat;
            tmp.v_end = end_stat;
            tmp.v_name = train_no_str;
            tmp.v_type = (train_no_str[0] == 'C') ? 0 : 1;
            tmp.start_day = start_time_str.substr(0,start_time_str.find(" "));
            tmp.end_day = end_time_str.substr(0,end_time_str.find(" "));
            tmp.start_clock = start_time_str.substr(start_time_str.find(" ")+1,std::string::npos);
            tmp.end_clock = end_time_str.substr(end_time_str.find(" ")+1,std::string::npos);
            int hours,minutes,seconds;
            std::sscanf(tmp.start_clock.c_str(),"%d:%d:%d",&hours,&minutes,&seconds);
            tmp.start_time = day_judger(tmp.start_day) + hours * 3600 + minutes * 60 + seconds;
            std::sscanf(tmp.end_clock.c_str(),"%d:%d:%d",&hours,&minutes,&seconds);
            tmp.end_time = day_judger(tmp.end_day) + hours * 3600 + minutes * 60 + seconds;
            tmp.length = tmp.end_time - tmp.start_time;
            tmp.price = std::stod(price_str);

            if (tmp.start_time < 0 || tmp.end_time < 0 || (cities.find(tmp.v_start) == cities.end()) || (cities.find(tmp.v_end) == cities.end())) {
                // we have got a wrong data base
                log = log + "添加失败，输入不合法\n";
                return ;
            }

            log = log + "添加成功\n";
            search_route_log->setPlainText(log);
            v.push_back(tmp);

        } else if (route_mode == DEL_OP) {
            search_route_log->setPlainText("删除成功");

        }
        add_route->setText("添加路线");
        del_route->setText("删除路线");
        search_route_start->setText("搜索路线 起点");
        search_route_end->setText("终点");
        search_route_num->setText("车次");
    }
}
void MainWindow::del_route_func() {
    if (del_route->text() == "删除路线") {

        add_route->setText("确认");
        del_route->setText("取消");
        search_route_log->setPlainText("确认删除");
        route_mode = DEL_OP;
        search_city_log->setReadOnly(true);
    } else {
        search_city_log->setReadOnly(false);
        search_route_log->setPlainText("操作取消");
        search_route_start->setText("搜索路线 起点");
        search_route_end->setText("终点");
        search_route_num->setText("车次");
        add_route->setText("添加路线");
        del_route->setText("删除路线");
    }
}
