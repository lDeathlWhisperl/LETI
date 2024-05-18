#include "advanced.h"
#include "ui_advanced.h"
#include <QtSql>

Advanced::Advanced(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Advanced),
    re(new QRegularExpression)
{
    ui->setupUi(this);

    QSqlQuery query;
    query.exec("CREATE TEMP TABLE temp AS SELECT date FROM incidents");
    re->setPattern("^(0[1-9]|[12][0-9]|3[12]).(0[1-9]|1[12]).(19[0-9][0-9]|20[0-2][0-9])$");
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
    if(!re->match(date_start).hasMatch() || !re->match(date_end).hasMatch()) return;

    int c1 = 0;
    int c2 = 0;

    QSqlQuery query;
    query.exec("DELETE FROM temp");

    QString ins = "";
    query.exec("SELECT date FROM incidents ORDER BY date DESC");
    while(query.next())
        ins += "(\'" + query.value(0).toString() + "\'), ";

    query.exec("INSERT INTO temp VALUES " + ins + "(\'" + date_start + "\'), (\'" + date_end + "\')");

    query.exec("SELECT MAX(row) "
               "FROM (SELECT ROW_NUMBER() OVER() AS row, date "
                     "FROM (SELECT * "
                           "FROM temp "
                           "ORDER BY date DESC)) "
               "WHERE date = \'" + date_start + "\'");

    if(query.next()) c1 = query.value(0).toInt();

    query.exec("SELECT MIN(row) "
               "FROM (SELECT ROW_NUMBER() OVER() AS row, date "
                     "FROM (SELECT * "
                           "FROM temp "
                           "ORDER BY date DESC)) "
               "WHERE date = \'" + date_end + "\'");

    if(query.next()) c2 = query.value(0).toInt();

    ui->L_inc_count->setText(": " + QString::number(c1 - c2 - 1));
}

void Advanced::on_LE_reg_id_editingFinished()
{
    QString text = ui->LE_reg_id->text();

    QSqlQuery query;
    query.exec("SELECT COUNT(incident_id) FROM relations WHERE registration_id = " + text);

    if(query.next()) text = query.value(0).toString();


    switch(text.size())
    {
    case 0: return;
    case 1:
        if(text[text.size()-1] == '1')
            ui->L_pers_count->setText(text + " происшествии");
        else
            ui->L_pers_count->setText(text + " происшествиях");
        break;
    default:
        if(text[text.size()-1] == '1' && text[text.size()-2] != '1')
            ui->L_pers_count->setText(text + " происшествии");
        else
            ui->L_pers_count->setText(text + " происшествиях");
    }
}


void Advanced::on_PB_get_protocol_clicked()
{

}

