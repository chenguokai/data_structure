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

        } else if (city_mode == DEL_OP) {
            search_city_log->setPlainText("删除城市 成功");
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
    search_city_log->setPlainText("开始搜索");
}
void MainWindow::start_route_search() {
    search_route_log->setPlainText("开始搜索");
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
        search_city_log->setReadOnly(true);

    } else {
        // confirm the operationn
        if (route_mode == ADD_OP) {
            search_route_log->setPlainText("添加成功");
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
