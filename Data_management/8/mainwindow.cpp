#include <QtSql>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "info.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    info(new Info(this))
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../collection");

    if(!db.open()) qFatal() << "DB did not open";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    info->close();
}

void MainWindow::on_PB_add_clicked()
{
    QString number = ui->LE_number->text();
    QString country = ui->LE_country->text();
    QString serial_number = ui->LE_serial_number->text();
    QString serial_theme = ui->LE_serial_theme->text();
    QString year = ui->LE_year->text();
    QString color = ui->LE_color->text();
    QString size = ui->LE_size->text();
    QString price = ui->LE_price->text();
    QString stamp_theme = ui->LE_stamp_theme->text();

    QSqlQuery query;
    query.exec("INSERT INTO stamp "
               "VALUES (" + number + ", \'" + country + "\', " + serial_number + ", \'" + serial_theme + "\', " + year + ", \'" + color + "\', \'" + size + "\', " + price + ", \'" + stamp_theme + "\')");
}

void MainWindow::on_PB_del_clicked()
{
    QString theme = ui->LE_del_theme->text();
    QSqlQuery query;
    query.exec("DELETE FROM stamp "
               "WHERE serial_theme = \'" + theme + "\'");
}


void MainWindow::on_PB_th_country_clicked()
{
    info->close();
    info->setWindowTitle("Страны");

    QString theme = ui->LE_cnt_theme->text(), result = "";
    QSqlQuery query;
    QMap<QString, int> map;
    query.exec("SELECT country "
               "FROM stamp "
               "WHERE serial_theme = \'" + theme + "\'");

    while(query.next())
        map[query.value(0).toString()]++;

    for(const auto& [key, value] : map.asKeyValueRange())
        result += key + " - " + QString::number(value) + ", ";

    result.removeLast();
    result.removeLast();

    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

