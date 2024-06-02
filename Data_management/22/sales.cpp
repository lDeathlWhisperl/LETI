#include <QtSql>

#include "sales.h"
#include "ui_sales.h"
#include "historytable.h"
#include "producttable.h"
#include "salesmen.h"

Sales::Sales(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Salesman),
    table(new historytable(this)),
    salesmen(new Salesmen(this))
{
    ui->setupUi(this);

    connect(this, SIGNAL(dataChanged()), ProductTable::getInstance(), SLOT(updateEntries()));
}

Sales::~Sales()
{
    delete ui;
}

void Sales::closeEvent(QCloseEvent*)
{
    table->close();
    salesmen->close();
}

bool Sales::isValid(QString name, double fees, QString sold_item, int sold_amount, QString date)
{
    QRegularExpression re;
#define CHECKMATCH(arg) if(!re.match(arg).hasMatch()) return false;

    re.setPattern("^[A-ZА-Я][a-zа-я]* ([A-ZА-Я][a-zа-я]*( [A-ZА-Я][a-zа-я]*)?|[A-ZА-Я]. ?([A-ZА-Я].)?)$");
    CHECKMATCH(name);

    re.setPattern("^(0|0.[0-9][0-9]?)$");
    CHECKMATCH(QString::number(fees));

    re.setPattern("^[A-zА-я][a-zа-я]*( ([A-zА-я][a-zа-я]*))*( \"([A-zА-я][a-zа-я]* ?)*\")?$");
    CHECKMATCH(sold_item);

    re.setPattern("^(1|[1-9][0-9]*)$");
    CHECKMATCH(QString::number(sold_amount));

    re.setPattern("^(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).20[0-2][0-9]$");
    CHECKMATCH(date);

    qDebug() << "Valid";
    return true;
}

bool Sales::p_isExist(QString item, int sp)
{
    QSqlQuery query;
    query.exec("SELECT * FROM product "
               "WHERE name = \'" + item + "\' AND sale_price = " + QString::number(sp));

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

bool Sales::h_isExist(QString item, int amount, QString date)
{
    QSqlQuery query;
    query.exec("SELECT * FROM history "
               "WHERE sold_item = \'" + item + "\' AND sold_amount = " + QString::number(amount) + " AND date = \'" + date + "\'");
    qDebug() << query.lastError().text();

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

bool Sales::s_isExist(QString name, double fees)
{
    QSqlQuery query;
    query.exec("SELECT * FROM salesmen "
               "WHERE name = \'" + name + "\' AND fees = " + QString::number(fees));

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

int Sales::getId(QString name, double fees, const double award)
{
    QSqlQuery query;
    int id = 0;

    query.exec("SELECT id FROM salesmen "
               "WHERE name = \'" + name + "\' AND fees = " + QString::number(fees));

    if(query.next())
    {
        id = query.value(0).toInt();
        query.exec("UPDATE salesmen "
                   "SET award = award + " + QString::number(award) + " "
                   "WHERE name = \'" + name + "\'");
    }
    return id;
}

void Sales::backupAward(QString name, QString item, int amount)
{
    QSqlQuery query;
    double award = 0;

    query.exec("SELECT sale_price FROM product WHERE name = \'" + item + "\'");
    if(query.next()) award = amount * query.value(0).toInt();

    query.exec("SELECT fees FROM salesmen WHERE name = \'" + name + "\'");
    if(query.next()) award *= query.value(0).toDouble();

    query.exec("UPDATE salesmen "
               "SET award = award - " + QString::number(award) + " "
               "WHERE name = \'" + name + "\'");
}

void Sales::on_PB_add_clicked()
{
    QString name = ui->LE_name->text();
    double fees = ui->LE_fees->text().toDouble();
    QString sold_item = ui->LE_sold_item->text();
    int sold_amount = ui->LE_sold_amount->text().toInt();
    QString date = ui->LE_date->text();
    int sale_price = ui->LE_sale_price->text().toInt();

    if(!isValid(name, fees, sold_item, sold_amount, date) || !p_isExist(sold_item, sale_price) || !s_isExist(name, fees)) return;

    double award = sale_price * sold_amount * fees;
    QSqlQuery query;

    int unit = 0;
    query.exec("SELECT unit FROM product "
               "WHERE name = \'" + sold_item + "\' AND sale_price = " + QString::number(sale_price));

    if(query.next())
    {
        unit = query.value(0).toInt();
        if(unit - sold_amount < 0)
        {
            sold_amount = unit;
            unit = 0;
        }
        else
            unit -= sold_amount;
    }

    int salesman_id = getId(name, fees, award), id = 0;
    query.exec("UPDATE product SET unit = " + QString::number(unit) + " " +
               "WHERE name = \'" + sold_item + "\' AND sale_price = " + QString::number(sale_price));
    query.exec("SELECT MAX(id)+1 FROM history");
    if(query.first()) id = query.value(0).toInt();

    query.exec("INSERT INTO history "
               "VALUES (" + QString::number(id) + ", " + QString::number(salesman_id) + ", \'" + sold_item + "\', " + QString::number(sold_amount) + ", \'" + date + "\')");

    emit dataChanged();
}

void Sales::on_PB_delete_clicked()
{
    QString name = ui->LE_del_name->text();
    QString item = ui->LE_del_item->text();
    int amount = ui->LE_del_amount->text().toInt();
    QString date = ui->LE_del_date->text();

    QSqlQuery query("SELECT fees FROM salesmen WHERE name = \'" + name + "\'");
    double fees = 0;
    if(query.first()) fees = query.value(0).toDouble();

    if(!isValid(name, 0, item, amount, date) || !h_isExist(item, amount, date) || !s_isExist(name, fees)) return;

    int id = getId(name, fees, 0);

    query.exec("SELECT sold_amount "
               "FROM history "
               "WHERE salesman_id = " + QString::number(id) + " AND sold_item = \'" + item + "\' AND sold_amount = " + QString::number(amount) + " AND date = \'" + date + "\'");

    int sold_amount = 0;
    if(query.first()) sold_amount = query.value(0).toInt();

    query.exec("UPDATE product "
               "SET unit = unit + " + QString::number(sold_amount) + " "
               "WHERE name = \'" + item + "\'");

    backupAward(name, item, amount);

    query.exec("SELECT MIN(id) FROM history "
               "WHERE sold_item = \'" + item + "\' AND sold_amount = " + QString::number(amount) + " AND date = \'" + date + "\'");
    if(query.first()) id = query.value(0).toInt();

    query.exec("DELETE FROM history "
               "WHERE id = " + QString::number(id));

    emit dataChanged();
}

void Sales::on_PB_history_clicked()
{
    table->updateEntries();
    table->show();
}


void Sales::on_PB_salesmen_clicked()
{
    salesmen->updateEntries();
    salesmen->show();
}

