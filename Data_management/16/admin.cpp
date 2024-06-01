#include <QtSql>

#include "admin.h"
#include "ui_admin.h"

Admin::Admin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);
}

Admin::~Admin()
{
    delete ui;
}

void Admin::on_PB_add_group_clicked()
{
    QString name =ui->LE_name->text();
    int year = ui->LE_year->text().toInt();
    QString country = ui->LE_country->text();
    QString members = ui->LE_members->text();
    int place = ui->LE_place->text().toInt();

    QSqlQuery query;
    query.exec("SELECT MAX(id) "
               "FROM groups");

    int id = 0;
    if(query.first()) id = query.value(0).toInt() + 1;

    query.exec("INSERT INTO groups "
               "VALUES (" + QString::number(id) + ", \'" + name + "\', " + QString::number(year) + ", \'" + country + "\', \'" + members + "\', " + QString::number(place) + ")");
}

void Admin::on_PB_add_song_clicked()
{
    QString name     = ui->LE_2_name->text();
    QString s_name   = ui->LE_song_name->text();
    QString composer = ui->LE_composer->text();
    QString autor    = ui->LE_autor->text();
    int year         = ui->LE_2_year->text().toInt();

    QSqlQuery query("SELECT id "
                    "FROM groups "
                    "WHERE name = \'" + name + "\'");

    int id = 0;
    if(query.first())
        id = query.value(0).toInt();
    else return;

    query.exec("INSERT INTO song "
               "VALUES (" + QString::number(id) + ", \'" + s_name + "\', \'" + composer + "\', \'" + autor + "\', " + QString::number(year) + ")");
}

void Admin::on_PB_add_tour_clicked()
{
    QString name = ui->LE_name_3->text();
    QString tour = ui->LE_tour_name->text();
    QString date_s = ui->LE_date_start->text();
    QString date_e = ui->LE_date_end->text();
    double price = ui->LE_price->text().toDouble();

    QSqlQuery query("SELECT id "
                    "FROM groups "
                    "WHERE name = \'" + name + "\'");

    int id = 0;
    if(query.first())
        id = query.value(0).toInt();
    else return;

    query.exec("INSERT INTO tour "
               "VALUES (" + QString::number(id) + ", \'" + tour + "\', \'" + date_s + "\', \'" + date_e + "\', " + QString::number(price) + ")");

    qDebug() << "VALUES (" + QString::number(id) + "\', \'" + tour + "\', \'" + date_s + "\', \'" + date_e + "\', " + QString::number(price) + ")" << query.lastError().text();
}

void Admin::on_PB_ch1_clicked()
{
    QString name = ui->LE_ch1_name->text();
    int place = ui->LE_ch1_place->text().toInt();

    QSqlQuery query;
    query.exec("UPDATE groups "
               "SET hit_parade = " + QString::number(place) + " " +
               "WHERE name = \'" + name + "\'");
}

void Admin::on_PB_ch2_clicked()
{
    QString name = ui->LE_ch2_name->text();
    QString mems = ui->LE_ch2_members->text();

    QSqlQuery query;
    query.exec("UPDATE groups "
               "SET members = \'" + mems + "\' " +
               "WHERE name = \'" + name + "\'");
}
