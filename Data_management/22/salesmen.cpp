#include <QtSql>

#include "salesmen.h"
#include "ui_salesmen.h"
#include "sales.h"

Salesmen::Salesmen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Salesmen)
{
    ui->setupUi(this);

    auto prnt = static_cast<Sales*>(parent);
    if(!prnt) qFatal() << "Something went wrong...";

    connect(prnt, SIGNAL(dataChanged()), this, SLOT(updateEntries()));
    connect(this, SIGNAL(dataChanged()), this, SLOT(updateEntries()));
}

void Salesmen::resizeEvent(QResizeEvent *)
{
    for(int i = 0; i < 3; ++i)
        ui->TW_salesmen->setColumnWidth(i, ui->TW_salesmen->geometry().width() / 3);
}

void Salesmen::updateEntries()
{
    ui->TW_salesmen->setRowCount(0);
    QSqlQuery query;
    query.exec("SELECT * FROM salesmen");

    while(query.next())
    {
        ui->TW_salesmen->insertRow(ui->TW_salesmen->rowCount());
        for(int i = 1; i <= 3; ++i)
            ui->TW_salesmen->setItem(ui->TW_salesmen->rowCount()-1, i-1, new QTableWidgetItem(query.value(i).toString()));
    }
}

bool Salesmen::isValid(QString name, double fees, int id)
{
    QRegularExpression re;
#define CHECKMATCH(arg) if(!re.match(arg).hasMatch()) return false;

    re.setPattern("^[A-ZА-Я][a-zа-я]* ([A-ZА-Я][a-zа-я]*( [A-ZА-Я][a-zа-я]*)?|[A-ZА-Я]. ?([A-ZА-Я].)?)$");
    CHECKMATCH(name);

    re.setPattern("^(0|0.[0-9][0-9]?)$");
    CHECKMATCH(QString::number(fees));

    re.setPattern("^(0|[1-9][0-9]*)$");
    CHECKMATCH(QString::number(id));

    qDebug() << "Valid";

    return true;
}

Salesmen::~Salesmen()
{
    delete ui;
}

void Salesmen::on_PB_hire_clicked()
{
    QString name = ui->LE_name->text();
    double fees = ui->LE_fees->text().toDouble();

    if(!isValid(name, fees, 0)) return;

    int id = 0;
    QSqlQuery query("SELECT MAX(id) FROM salesmen");
    if(query.first()) id = query.value(0).toInt()+1;
    query.exec("INSERT INTO salesmen VALUES (" + QString::number(id) + ", \'" + name + "\', " + QString::number(fees) + ", 0)");

    emit dataChanged();
}


void Salesmen::on_PB_fire_clicked()
{
    QString name = ui->LE_name->text();
    double fees = ui->LE_fees->text().toDouble();
    int line = ui->LE_line->text().toInt();

    if(!isValid(name, fees, line)) return;

    QSqlQuery query;
    query.exec("DELETE FROM salesmen WHERE id = " + QString::number(line));
    emit dataChanged();
}

