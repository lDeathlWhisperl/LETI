#include <QtSql>

#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manager)
{
    ui->setupUi(this);
}

void Manager::resizeEvent(QResizeEvent*e)
{
    for(int i = 0; i < 5; ++i)
        ui->TW_table->setColumnWidth(i, ui->TW_table->geometry().width() / 5);
}

void Manager::initTable()
{
    QSqlQuery query("SELECT * "
                    "FROM groups");
    auto* table = ui->TW_table;

    while(query.next())
    {
        table->insertRow(table->rowCount());
        for(int i = 1; i <= 5; ++i)
            table->setItem(table->rowCount()-1, i-1, new QTableWidgetItem(query.value(i).toString()));
    }
}

Manager::~Manager()
{
    delete ui;
}

void Manager::on_PB_2_year_cnt_clicked()
{
    QSqlQuery query("SELECT year, country "
                    "FROM groups "
                    "WHERE name = \'" + ui->LE_2_name->text() + "\'");

    if(query.next())
        ui->L_2_text->setText(query.value(1).toString() + " - " + query.value(0).toString());
    else
        ui->L_2_text->setText("Группа не найдена");
}


void Manager::on_PB_3_popular_clicked()
{
    QSqlQuery query("SELECT MIN(hit_parade) AS min, id "
                    "FROM groups");
    int id = 0;

    if(query.first())
        id = query.value(1).toInt();

    QString name = "", result = "";
    query.exec("SELECT name "
               "FROM groups "
               "WHERE id = " + QString::number(id));
    if(query.first()) name = query.value(0).toString();

    query.exec("SELECT name "
               "FROM song "
               "WHERE group_id = " + QString::number(id));

    result = "Группа: " + name + "\nРепертуар:\n";
    while(query.next())
        result += "  > " + query.value(0).toString() + "\n";
    ui->L_3_text->setText(result);
}


void Manager::on_PB_4_info_clicked()
{
    QSqlQuery query("SELECT autor, composer, year "
                    "FROM song "
                    "WHERE name = \'" + ui->LE_4_name->text() + "\'");

    if(query.next())
        ui->L_4_text->setText("Автор: " + query.value(0).toString() + "\n" +
                              "Композитор: " + query.value(1).toString() + "\n" +
                              "Год: " + query.value(2).toString());
    else
        ui->L_4_text->setText("Песня не найдена");
}


void Manager::on_PB_5_tour_clicked()
{
    QString name = ui->LE_5_name->text();
    QSqlQuery query("SELECT id "
                    "FROM groups "
                    "WHERE name = \'" + name + "\'");
    int id = 0;

    if(query.first()) id = query.value(0).toInt();

    query.exec("SELECT name, date_start, date_end "
               "FROM tour "
               "WHERE group_id = " + QString::number(id));

    if(query.first())
        ui->L_5_text->setText("Название: " + query.value(0).toString() +
                              "\nДата начала: " + query.value(1).toString() +
                              "\nДата окончания: " + query.value(2).toString());
    else
        ui->L_5_text->setText("Не найдено");
}


void Manager::on_PB_6_price_clicked()
{
    QString name = ui->LE_6_name->text();
    QSqlQuery query("SELECT id "
                    "FROM groups "
                    "WHERE name = \'" + name + "\'");
    int id = 0;

    if(query.first()) id = query.value(0).toInt();

    query.exec("SELECT ticket_price "
               "FROM tour "
               "WHERE group_id = " + QString::number(id));

    if(query.first())
        ui->L_6_text->setText("Цена билета на концерт " + name + ": " + query.value(0).toString());
    else
        ui->L_6_text->setText("Не найдено");
}


void Manager::on_PB_7_mem_clicked()
{
    QString name = ui->LE_7_name->text();
    QSqlQuery query("SELECT members "
                    "FROM groups "
                    "WHERE name = \'" + name + "\'");

    if(query.first())
    {
        QString t = query.value(0).toString();
        for(auto& str : t) if(str == ' ') str = '\n';
        ui->L_7_text->setText("Состав группы " + name + ":\n" + t);
    }
    else
        ui->L_7_text->setText("Не найдено");
}

