#include <QtSql>
#include <QKeyEvent>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

void setColumnWidth(QTableWidget* table, int col_cnt)
{
    for(int i = 0; i < col_cnt; ++i)
        table->setColumnWidth(i, table->geometry().width() / col_cnt);
}

int row_to_id(int row, QString table_name)
{
    QSqlQuery query;
    query.exec("SELECT ROW_NUMBER() OVER()-1 AS row, id FROM " + table_name);

    while(query.next())
        if(query.value(0).toInt() == row)
            return query.value(1).toInt();

    return -1;
}

int id_to_row(int id, QString table_name)
{
    QSqlQuery query;
    query.exec("SELECT ROW_NUMBER() OVER()-1 AS row, id FROM " + table_name);

    while(query.next())
        if(query.value(1).toInt() == id)
            return query.value(0).toInt();

    return -1;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../Database/incidents.db");

    if(!db.open())
        qFatal() << "\x1b[30;41mDatabase was not open\x1b[0m";

    sync();
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    setColumnWidth(ui->TW_messages, 5);
    setColumnWidth(ui->TW_persons, 6);
    setColumnWidth(ui->TW_relations, 3);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() != Qt::Key_Delete || del_id == -1) return;

    int row = id_to_row(del_id, table);
    QSqlQuery query;
    query.exec("DELETE FROM " + table + " WHERE id = " + QString::number(del_id));
    qDebug() << "DELETE FROM " + table + " WHERE id = " + QString::number(del_id);

    if(table == "incidents")
        ui->TW_messages->removeRow(row);
    else if(table == "persons")
    {}
    else if(table == "relation")
    {}

    del_id = -1;
}

void MainWindow::sync()
{
    QSqlQuery query;

    query.exec("SELECT * FROM incidents");
    while(query.next())
    {
        ui->TW_messages->insertRow(ui->TW_messages->rowCount());
        for(int i = 0; i < 5; ++i)
            ui->TW_messages->setItem(ui->TW_messages->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    query.exec("SELECT * FROM persons");
    while(query.next())
    {
        ui->TW_persons->insertRow(ui->TW_persons->rowCount());
        for(int i = 0; i < 6; ++i)
            ui->TW_persons->setItem(ui->TW_persons->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    query.exec("SELECT * FROM relation");
    while(query.next())
    {
        ui->TW_relations->insertRow(ui->TW_relations->rowCount());
        for(int i = 0; i < 3; ++i)
            ui->TW_relations->setItem(ui->TW_relations->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    isSync = true;
}

void MainWindow::on_PB_m_entry_clicked()
{
    ui->TW_messages->insertRow(ui->TW_messages->rowCount());

    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM incidents");

    int id = -1;
    if(query.next()) id = query.value(0).toInt() + 1;

    query.exec("INSERT INTO incidents VALUES (\'0\', \' \', \' \', \' \', \' \', " + QString::number(id) + ")");
    qDebug() << "INSERT INTO incidents VALUES (\'0\', \' \', \' \', \' \', \' \', " + QString::number(id) + ")";
}


void MainWindow::on_PB_p_entry_clicked()
{
    ui->TW_persons->insertRow(ui->TW_persons->rowCount());
}


void MainWindow::on_PB_r_entry_clicked()
{
    ui->TW_relations->insertRow(ui->TW_relations->rowCount());
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}


void MainWindow::on_TW_messages_cellChanged(int row, int column)
{
    if(!isSync) return;

    QString col_name;
    switch(column)
    {
    case 0:
        col_name = "message_id";
        break;
    case 1:
        col_name = "date";
        break;
    case 2:
        col_name = "type";
        break;
    case 3:
        col_name = "conclusion";
        break;
    case 4:
        col_name = "criminal_id";
        break;
    }

    QSqlQuery query;
    query.exec("SELECT ROW_NUMBER() OVER()-1 AS row, id FROM incidents");

    int id = row_to_id(row, "incidents");

    query.exec("UPDATE incidents SET " + col_name + " = \'" + ui->TW_messages->item(row, column)->text() + "\' WHERE id = " + QString::number(id));
    qDebug() << "UPDATE incidents SET " + col_name + " = \'" + ui->TW_messages->item(row, column)->text() + "\' WHERE id = " + QString::number(id);
}


void MainWindow::on_TW_messages_cellClicked(int row, int)
{
    table = "incidents";
    del_id = row_to_id(row, table);
}

