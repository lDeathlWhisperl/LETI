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

void MainWindow::on_PB_add_coll_clicked()
{
    QString stamp_id = ui->LE_add_stamp_id->text();
    QString section_number = ui->LE_add_sec_num->text();
    QString page_position = ui->LE_add_page_pos->text();

    QSqlQuery query;
    query.exec("INSERT INTO collection "
               "VALUES (" + stamp_id + ", " + section_number + ", \'" + page_position + "\')");
    qDebug() << "INSERT INTO collection "
                "VALUES (" + stamp_id + ", " + section_number + ", \'" + page_position + "\')" << query.lastError().text();
}

void MainWindow::on_PB_add_sec_clicked()
{
    QString id = ui->LE_add_sec_num_2->text();
    QString volume = ui->LE_add_vol->text();
    QString theme =ui->LE_add_theme->text();
    QString country = ui->LE_add_cnt->text();

    QSqlQuery query;
    query.exec("INSERT INTO section "
               "VALUES (" + id + ", " + volume + ", \'" + theme + "\', \'" + country + "\')");
    qDebug() <<"INSERT INTO section "
                "VALUES (" + id + ", " + volume + ", \'" + theme + "\', \'" + country + "\')"<< query.lastError().text();
}

void MainWindow::on_PB_del_clicked()
{
    QString theme = ui->LE_del_theme->text();
    QSqlQuery query;
    query.exec("DELETE FROM stamp "
               "WHERE serial_theme = \'" + theme + "\'");
}

void MainWindow::on_PB_ch_pos_clicked()
{
    QString number = ui->LE_ch_number->text();
    QString position = ui->LE_ch_pos->text();

    QSqlQuery query("SELECT * "
                    "FROM collection "
                    "WHERE page_position = \'" + position + "\'");

    if(query.first())
    {
        QString buffer;
        QString stamp_id;
        query.exec("SELECT page_position "
                   "FROM collection "
                   "WHERE stamp_id = " + number);
        if(query.first()) buffer = query.value(0).toString();

        query.exec("UPDATE collection "
                   "SET page_position = '-' "
                   "WHERE stamp_id = " + number);
        query.exec("SELECT stamp_id "
                   "FROM collection "
                   "WHERE page_position = \'" + position + "\'");
        if(query.first()) stamp_id = query.value(0).toString();

        query.exec("UPDATE collection "
                   "SET page_position = \'" + buffer + "\' "
                   "WHERE stamp_id = " + stamp_id);
        query.exec("UPDATE collection "
                   "SET page_position = \'" + position + "\' "
                   "WHERE stamp_id = " + number);
    }
    else
    {
        query.exec("UPDATE collection "
                   "SET page_position = \'" + position + "\' "
                   "WHERE stamp_id = " + number);
    }
}

void MainWindow::on_PB_sec_find_country_clicked()
{
    info->close();
    info->setWindowTitle("Страны");

    QString section = ui->LE_section->text(), result = "";
    QSqlQuery query("SELECT country "
                    "FROM section "
                    "WHERE volume = " + section);

    while(query.next()) result += query.value(0).toString() + "\n";

    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_th_country_clicked()
{
    info->close();
    info->setWindowTitle("Страны");

    QString theme = ui->LE_cnt_theme->text(), result = "";
    QSqlQuery query("SELECT COUNT(country) AS cnt, country "
                    "FROM stamp WHERE serial_theme = \'" + theme + "\' "
                    "GROUP BY country");

    while(query.next())
        result += query.value(1).toString() + " - " + query.value(0).toString() + "\n";

    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_find_volume_clicked()
{
    info->close();
    info->setWindowTitle("Тома");

    QString serial = ui->LE_serial->text(), result = "";
    QSqlQuery query("SELECT volume "
                    "FROM section WHERE theme = \'" + serial + "\' "
                    "GROUP BY volume");

    while(query.next()) result += query.value(0).toString() + "\n";
    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_find_pos_clicked()
{
    info->close();
    info->setWindowTitle("Страница и позиция");

    QString theme = ui->LE_fnd_theme->text(), result = "";
    QSqlQuery query("SELECT id "
                    "FROM section "
                    "WHERE theme = \'" + theme + "\'"), q;

    while(query.next())
    {
        q.exec("SELECT page_position "
               "FROM collection "
               "WHERE section_number = " + query.value(0).toString());
        while(q.next()) result += q.value(0).toString() + "\n";

    }
    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_find_theme_clicked()
{
    info->close();
    info->setWindowTitle("Темы");

    QString size = ui->LE_fnd_size->text(), result = "";
    QSqlQuery query("SELECT serial_theme "
                    "FROM stamp "
                    "WHERE size = \'" + size + "\' "
                    "GROUP BY serial_theme");

    while(query.next()) result += query.value(0).toString() + "\n";
    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_pos_find_country_clicked()
{
    info->close();
    info->setWindowTitle("Страна");

    QString position = ui->LE_fnd_pos->text(), result = "", id = "";
    QSqlQuery query("SELECT section_number "
                    "FROM collection "
                    "WHERE page_position = \'" + position + "\'");

    if(query.first()) id = query.value(0).toString();
    query.exec("SELECT country "
               "FROM section "
               "WHERE id = " + id);
    if(query.first()) result = query.value(0).toString();
    if(result.isEmpty()) result = "Не найдено";

    info->setText(result);
    info->show();
}

void MainWindow::on_PB_report_clicked()
{
    info->close();
    info->setWindowTitle("Отчет");

    QSqlQuery query("SELECT COUNT(serial_theme) AS cnt, serial_theme "
                    "FROM stamp "
                    "GROUP BY serial_theme");

    QString report = "Количество и названия тем:\n";
    while(query.next()) report += query.value(1).toString() + " - " + query.value(0).toString() + "\n";

    report += "Страны по разделам:\n";
    query.exec("SELECT country, id "
               "FROM section");
    while(query.next()) report += query.value(0).toString() + " - раздел №" + query.value(1).toString() + "\n";

    report += "Количество марок каждой страны:\n";
    query.exec("SELECT COUNT(country) AS cnt, country "
               "FROM stamp "
               "GROUP BY country");
    while(query.next()) report += query.value(1).toString() + " - " + query.value(0).toString() + "\n";

    report += "Количество страниц в коллекции: ";
    query.exec("SELECT page_position "
               "FROM collection");
    QSet<QString> set;
    while(query.next())
    {
        QString page = query.value(0).toString();
        int i = page.indexOf(":");
        page.truncate(i);
        set.insert(page);
    }
    report += QString::number(set.size());

    info->setText(report);
    info->show();
}
