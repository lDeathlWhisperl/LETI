#include <QtSql>

#include "shop.h"
#include "producttable.h"

#include "ui_shop.h"
#include "mainwindow.h"

Shop::Shop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shop),
    table(ProductTable::getInstance(this))
{
    ui->setupUi(this);

}

Shop::~Shop()
{
    delete ui;
}

void Shop::closeEvent(QCloseEvent*)
{
    table->close();
}

bool Shop::isExists(QString name, int unit, int purchase_price, int sale_price)
{
    QSqlQuery query;

    query.exec("SELECT name FROM product WHERE name = \'" + name + "\' AND purchase_price = " + QString::number(purchase_price) + " AND sale_price = " + QString::number(sale_price));
    if(query.next()) return true;

    query.exec("SELECT name FROM product WHERE name = \'" + name + "\' AND unit = " + QString::number(unit));
    if(query.next()) return true;

    return false;
}

void Shop::updateProduct(QString name, int unit)
{
    QSqlQuery query;
    query.exec("UPDATE product "
               "SET unit = unit + " + QString::number(unit) + " "
               "WHERE name = \'" + name + "\'");
    qDebug()<< "UPDATE product "
               "SET unit = unit + " + QString::number(unit) + " "
               "WHERE name = \'" + name + "\'" << query.lastError().text();
    emit dataChanged();
}

bool Shop::isValid(QString name, QString unit, QString pp, QString sp)
{
#define CHECKMATCH(arg) if(!re.match(arg).hasMatch()) return false;

    QRegularExpression re;

    re.setPattern("^[A-zА-я][a-zа-я]*( ([A-zА-я][a-zа-я]*))*( \"([A-zА-я][a-zа-я]* ?)*\")?$");
    CHECKMATCH(name);

    re.setPattern("^(1|[1-9][0-9]*)$");
    CHECKMATCH(unit);
    CHECKMATCH(pp);
    CHECKMATCH(sp);

    qDebug() << "Valid";
    return true;
}

void Shop::on_PB_addToBD_clicked()
{
    QString name = ui->LE_addProd->text();
    int unit = ui->LE_addAmount->text().toInt();
    int purchase_price = ui->LE_price->text().toInt();
    int sale_price = ui->LE_salePrice->text().toInt();

    if(!isValid(name, QString::number(unit), QString::number(purchase_price), QString::number(sale_price))) return;

    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM product");

    int id = 0;

    if(query.next())
        id = query.value(0).toInt() + 1;

    if(isExists(name, unit, purchase_price, sale_price))
    {
        updateProduct(name, unit);
        return;
    }

    query.exec("INSERT INTO product VALUES (" + QString::number(id) + ", \'" + name + "\', " + QString::number(unit) + ", " + QString::number(purchase_price) + ", " + QString::number(sale_price) + ")");
    emit dataChanged();
}


void Shop::on_PB_removeFromBD_clicked()
{
    QString name = ui->LE_removeProd->text();
    int unit = ui->LE_removeAmount->text().toInt();

    if(!isValid(name, QString::number(unit)) || !isExists(name, unit)) return;

    QSqlQuery query;
    query.exec("DELETE FROM product WHERE name = \'" + name + "\' AND unit = " + QString::number(unit));
    emit dataChanged();
}


void Shop::on_PB_getAllProducts_clicked()
{
    table->updateEntries();
    table->show();
}

