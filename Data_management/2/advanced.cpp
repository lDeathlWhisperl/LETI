#include <QtSql>

#include "report.h"
#include "advanced.h"
#include "ui_advanced.h"

Advanced::Advanced(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Advanced),
    re(new QRegularExpression),
    report(new Report(this))
{
    ui->setupUi(this);

    re->setPattern("^(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).(19[0-9][0-9]|20[0-2][0-9])$");
    connect(this, SIGNAL(dateChanged()), this, SLOT(getIncidentsCount()));
}

Advanced::~Advanced()
{
    delete ui;
    delete report;
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

    date_start = QDate::fromString(date_start, "dd.MM.yyyy").toString("yyyy.MM.dd");
    date_end = QDate::fromString(date_end, "dd.MM.yyyy").toString("yyyy.MM.dd");

    QSqlQuery query("SELECT COUNT(date) FROM incidents WHERE date BETWEEN \'" + date_start + "\' AND \'" + date_end + "\'");
    qDebug() << "SELECT COUNT(date) FROM incidents WHERE date BETWEEN \'" + date_start + "\' AND \'" + date_end + "\'";

    if(query.first()) ui->L_inc_count->setText(query.value(0).toString());
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
    QString num = ui->LE_inc_prot->text();
    QRegularExpression re("^[1-9][0-9]*$");

    if(!re.match(num).hasMatch()) return;

    report->setWindowTitle("Отчет по происшествию №" + num);
    report->show();
    report->generate(num);
}

