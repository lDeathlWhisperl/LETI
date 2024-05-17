#include "advanced.h"
#include "ui_advanced.h"
#include <QtSql>

Advanced::Advanced(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Advanced)
{
    ui->setupUi(this);

    connect(this, SIGNAL(dateChanged()), this, SLOT(getIncidentsCount()));
}

Advanced::~Advanced()
{
    delete ui;
}

void Advanced::on_LE_date_s_editingFinished()
{
    date_start = ui->LE_date_s->text();
    emit dateChanged();
}


void Advanced::on_LE_date_e_editingFinished()
{
    date_end = ui->LE_date_e->text();
    emit dateChanged();
}

void Advanced::getIncidentsCount()
{
    if(date_start.isEmpty() || date_end.isEmpty()) return;

    int c1 = 0;
    int c2 = 0;

    //SELECT MIN(row) FROM (SELECT ROW_NUMBER() OVER() AS row, date FROM (SELECT date FROM incidents ORDER BY date DESC)) WHERE date = "01.01.1956";
    QSqlQuery query;
    query.exec("SELECT MAX(row) "
               "FROM (SELECT ROW_NUMBER() OVER() AS row, date "
                     "FROM (SELECT date "
                           "FROM incidents "
                           "ORDER BY date DESC)) "
               "WHERE date = \'" + date_start + "\'");
    if(query.next()) c1 = query.value(0).toInt();
    else ui->L_inc_count->setText(": 0");

    query.exec("SELECT MIN(row) "
               "FROM (SELECT ROW_NUMBER() OVER() AS row, date "
                     "FROM (SELECT date "
                           "FROM incidents "
                           "ORDER BY date DESC)) "
               "WHERE date = \'" + date_end + "\'");
    if(query.next()) c2 = query.value(0).toInt();
    else ui->L_inc_count->setText(": 0");

    ui->L_inc_count->setText(": " + QString::number(c1 - c2 + 1));
}
