#include <QtSql>

#include "salesman.h"
#include "ui_salesman.h"

//^[A-ZА-Я][a-zа-я]* ([A-ZА-Я][a-zа-я]*( [A-ZА-Я][a-zа-я]*)?|[A-ZА-Я]\. ?([A-ZА-Я]\.)?)$

Salesman::Salesman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Salesman)
{
    ui->setupUi(this);
}

Salesman::~Salesman()
{
    delete ui;
}

bool Salesman::isValid(QString name, double fees, QString sold_item, int sold_amount, QString date)
{
    QRegularExpression re;
#define CHECKMATCH(arg) if(!re.match(arg).hasMatch()) return false;

    re.setPattern("^[A-ZА-Я][a-zа-я]* ([A-ZА-Я][a-zа-я]*( [A-ZА-Я][a-zа-я]*)?|[A-ZА-Я]. ?([A-ZА-Я].)?)$");
    CHECKMATCH(name);
    qDebug() << 1;

    re.setPattern("^0.[0-9][0-9]?$");
    CHECKMATCH(QString::number(fees));
    qDebug() << 2;

    re.setPattern("^[A-zА-я][a-zа-я]*( ([A-zА-я]* ?)?(\"([A-zА-я][a-zа-я]*|[A-zА-я][a-zа-я]* [A-zА-я][a-zа-я]*)\")?)?$");
    CHECKMATCH(sold_item);
    qDebug() << 3;

    re.setPattern("^(1|[1-9][0-9]*)$");
    CHECKMATCH(QString::number(sold_amount));
    qDebug() << 4;

    re.setPattern("^(0[1-9]|[12][0-9]|3[12]).(0[1-9]|1[12]).(19[0-9][0-9]|20[0-2][0-9])$");
    CHECKMATCH(date);

    qDebug() << "Valid";
    return true;
}

bool Salesman::isExist(QString item, int sp)
{
    QSqlQuery query;
    query.exec("SELECT * FROM product WHERE name = \'" + item + "\' AND sale_price = " + QString::number(sp));
    qDebug() << "SELECT * FROM product WHERE name = \'" + item + "\' AND sale_price = " + QString::number(sp) << query.lastError().text();

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

void Salesman::on_PB_add_clicked()
{
    QString name = ui->LE_name->text();
    double fees = ui->LE_fees->text().toDouble();
    QString sold_item = ui->LE_sold_item->text();
    int sold_amount = ui->LE_sold_amount->text().toInt();
    QString date = ui->LE_date->text();
    int sale_price = ui->LE_sale_price->text().toInt();

    if(!isValid(name, fees, sold_item, sold_amount, date) || !isExist(sold_item, sale_price)) return;

}

void Salesman::on_PB_delete_clicked()
{

}

void Salesman::on_PB_history_clicked()
{

}

