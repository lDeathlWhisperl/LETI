#include <QtSql>

#include "salesman.h"
#include "ui_salesman.h"
#include "historytable.h"
#include "producttable.h"

Salesman::Salesman(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Salesman),
    table(new historytable(this))
{
    ui->setupUi(this);

    connect(this, SIGNAL(dataChanged()), ProductTable::getInstance(), SLOT(updateEntries()));
}

Salesman::~Salesman()
{
    delete ui;
}

void Salesman::closeEvent(QCloseEvent*)
{
    table->close();
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

    re.setPattern("^[A-zА-я][a-zа-я]*( ([A-zА-я][a-zа-я]*))*( \"([A-zА-я][a-zа-я]* ?)*\")?$");
    CHECKMATCH(sold_item);
    qDebug() << 3;

    re.setPattern("^(1|[1-9][0-9]*)$");
    CHECKMATCH(QString::number(sold_amount));
    qDebug() << 4;

    re.setPattern("^(0[1-9]|[12][0-9]|3[12]).(0[1-9]|1[12]).20[0-2][0-9]$");
    CHECKMATCH(date);

    qDebug() << "Valid";
    return true;
}

bool Salesman::isExist(QString item, int sp)
{
    QSqlQuery query;
    query.exec("SELECT * FROM product WHERE name = \'" + item + "\' AND sale_price = " + QString::number(sp));

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

bool Salesman::isExist(QString item, int amount, QString date)
{
    QSqlQuery query;
    query.exec("SELECT * FROM history WHERE sold_item = \'" + item + "\' AND sold_amount = " + QString::number(amount) + " AND date = \'" + date + "\'");
    qDebug() << query.lastError().text();

    if(!query.next()) return false;

    qDebug() << "Exists";
    return true;
}

int Salesman::getId(QString name, double fees, double award)
{
    QSqlQuery query;

    query.exec("SELECT id FROM salesmen WHERE name = \'" + name + "\'");
    if(query.next())
    {
        int id = query.value(0).toInt();
        query.exec("UPDATE salesmen SET award = award + " + QString::number(award));
        return id;
    }

    query.exec("SELECT MAX(id) FROM salesmen");
    int id = 0;
    if(query.next()) id = query.value(0).toInt()+1;

    query.exec("INSERT INTO salesmen VALUES (" + QString::number(id) + ", \'" + name + "\', " + QString::number(fees) + "," + QString::number(award) + ")");

    return id;
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

    double award = sale_price * sold_amount * fees;
    int id = getId(name, fees, award);
    QSqlQuery query;

    int unit = 0;
    query.exec("SELECT unit FROM product WHERE name = \'" + sold_item + "\' AND sale_price = " + QString::number(sale_price));

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

    query.exec("UPDATE product SET unit = " + QString::number(unit) + " WHERE name = \'" + sold_item + "\' AND sale_price = " + QString::number(sale_price));
    query.exec("INSERT INTO history VALUES (" + QString::number(id) + ", \'" + sold_item + "\', " + QString::number(sold_amount) + ", \'" + date + "\')");
    emit dataChanged();
}

void Salesman::on_PB_delete_clicked()
{
    QString name = ui->LE_del_name->text();
    QString item = ui->LE_del_item->text();
    int amount = ui->LE_del_amount->text().toInt();
    QString date = ui->LE_del_date->text();

    if(!isValid(name, 0.01, item, amount, date) || !isExist(item, amount, date)) return;

    int id = getId(name, 0, 0);


}

void Salesman::on_PB_history_clicked()
{
    table->updateEntries();
    table->show();
}

