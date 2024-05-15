#include <QtSql>
#include <QKeyEvent>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "advanced.h"

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

void backupField(QTableWidget* table, QString table_name , QString col_name, int row, int column, int id, bool &bckp, QString regex, QString w_message = "")
{
    QSqlQuery query;
    QRegularExpression re;
    //check if field is already exists
    query.exec("SELECT " + col_name + " FROM " + table_name + " WHERE id = " + QString::number(id));
    qDebug() << "SELECT registration_id FROM persons WHERE id = " + QString::number(id) << query.lastError().databaseText();

    re.setPattern(regex);
    auto match = re.match(table->item(row, column)->text());

    if(!match.hasMatch() && query.next())
    {
        bckp = true; //otherwise the next line calls the method twice
        table->item(row, column)->setText(query.value(0).toString());
        qDebug() << "\x1b[1;43m" << w_message << "\x1b[0m";
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    adv_opt(new Advanced(this))
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
    qDebug() << "DELETE FROM " + table + " WHERE id = " + QString::number(del_id) << query.lastError().databaseText();

    if(table == "incidents")
        ui->TW_messages->removeRow(row);
    else if(table == "persons")
        ui->TW_persons->removeRow(row);
    else if(table == "relations")
        ui->TW_relations->removeRow(row);

    del_id = -1;
}

void MainWindow::sync()
{
    qDebug() << "\x1b[1;42mSync started\x1b[1;0m";

    QSqlQuery query;

    query.exec("SELECT * FROM incidents");
    qDebug() << "SELECT * FROM incidents" << query.lastError().text();

    while(query.next())
    {
        ui->TW_messages->insertRow(ui->TW_messages->rowCount());
        for(int i = 0; i < 5; ++i)
            ui->TW_messages->setItem(ui->TW_messages->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    query.exec("SELECT * FROM persons");
    qDebug() << "SELECT * FROM persons" << query.lastError().text();

    while(query.next())
    {
        ui->TW_persons->insertRow(ui->TW_persons->rowCount());
        for(int i = 0; i < 6; ++i)
            ui->TW_persons->setItem(ui->TW_persons->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    query.exec("SELECT * FROM relations");
    qDebug() << "SELECT * FROM relations" << query.lastError().text();

    while(query.next())
    {
        ui->TW_relations->insertRow(ui->TW_relations->rowCount());
        for(int i = 0; i < 3; ++i)
            ui->TW_relations->setItem(ui->TW_relations->rowCount()-1, i, new QTableWidgetItem(query.value(i).toString()));
    }

    isSync = true;

    qDebug() << "\x1b[1;42mSync ended\x1b[1;0m";
}

void MainWindow::on_PB_m_entry_clicked()
{
    ui->TW_messages->insertRow(ui->TW_messages->rowCount());

    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM incidents");

    int id = -1;
    if(query.next()) id = query.value(0).toInt() + 1;

    query.exec("INSERT INTO incidents VALUES (\' \', \' \', \' \', \' \', \' \', " + QString::number(id) + ")");
    qDebug() << "INSERT INTO incidents VALUES (\' \', \' \', \' \', \' \', \' \', " + QString::number(id) + ")" << query.lastError().databaseText();

    ui->TW_messages->setItem(id_to_row(id, "incidents"), 1, new QTableWidgetItem("01.01.1900"));
}


void MainWindow::on_PB_p_entry_clicked()
{
    ui->TW_persons->insertRow(ui->TW_persons->rowCount());

    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM persons");

    int id = -1;
    if(query.next()) id = query.value(0).toInt() + 1;

    query.exec("INSERT INTO persons VALUES (\'" + QString::number(id) + "\', \' \', \' \', \' \', \' \', \' \', " + QString::number(id) + ")");
    qDebug() << "INSERT INTO persons VALUES (\'" + QString::number(id) + "\', \' \', \' \', \' \', \' \', \' \', " + QString::number(id) + ")" << query.lastError().databaseText();

    ui->TW_persons->setItem(id_to_row(id, "persons"), 0, new QTableWidgetItem(QString::number(id)));
}


void MainWindow::on_PB_r_entry_clicked()
{
    ui->TW_relations->insertRow(ui->TW_relations->rowCount());

    QSqlQuery query;
    query.exec("SELECT MAX(id) FROM relations");

    int id = -1;
    if(query.next()) id = query.value(0).toInt() + 1;

    query.exec("INSERT INTO relations VALUES (\'0\', \' \', \' \', " + QString::number(id) + ")");
    qDebug() << "INSERT INTO relations VALUES (\'0\', \' \', \' \', " + QString::number(id) + ")" << query.lastError().databaseText();
}

void MainWindow::on_TW_messages_cellChanged(int row, int column)
{
    if(!isSync) return;

    ///////////TEMPORARY///////////
    static bool isBackuped = false;
    if(isBackuped)
    {
        isBackuped = false;
        return ;
    }
    //////////////////////////////

    QSqlQuery query;
    int id = row_to_id(row, "incidents");
    QString col_name;

    switch(column)
    {
    case 0:
        col_name = "message_id";
        backupField(ui->TW_messages, "incidents", col_name, row, column, id, isBackuped, "^[1-9][0-9]*$", "This field exists already or has invalid id");
        break;
    case 1:
        col_name = "date";
        backupField(ui->TW_messages, "incidents", col_name, row, column, id, isBackuped, "^(0[1-9]|[12][0-9]|3[12]).(0[1-9]|1[12]).(19[0-9][0-9]|20[0-2][0-4])$", "Invalid date format: use DD.MM.YYYY format instead");
        break;
    case 2:
        col_name = "type";
        break;
    case 3:
        col_name = "conclusion";
        break;
    case 4:
        col_name = "criminal_id";
        backupField(ui->TW_messages, "incidents", col_name, row, column, id, isBackuped, "^[1-9][0-9]*$", "This field exists already or has invalid id");
        break;
    }

    if(isBackuped) return;

    query.exec("UPDATE incidents SET " + col_name + " = \'" + ui->TW_messages->item(row, column)->text() + "\' WHERE id = " + QString::number(id));
    qDebug() << "UPDATE incidents SET " + col_name + " = \'" + ui->TW_messages->item(row, column)->text() + "\' WHERE id = " + QString::number(id) << query.lastError().databaseText();
}


void MainWindow::on_TW_persons_cellChanged(int row, int column)
{
    if(!isSync) return;

    ///////////TEMPORARY///////////
    static bool isBackuped = false;
    if(isBackuped)
    {
        isBackuped = false;
        return ;
    }
    //////////////////////////////

    QString col_name;
    QSqlQuery query;
    int id = row_to_id(row, "persons");

    switch(column)
    {
    case 0:
        col_name = "registration_id";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^[1-9][0-9]*$", "This field exists already or has invalid id");
        break;
    case 1:
        col_name = "name";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^[A-Z][a-z]*$", "This field exists already or has invalid name");
        break;
    case 2:
        col_name = "surname";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^[A-Z][a-z]*$", "This field exists already or has invalid surname");
        break;
    case 3:
        col_name = "patronymic";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^([A-Z][a-z]|-| )*$", "This field exists already or has invalid name");
        break;
    case 4:
        col_name = "address";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^([A-Z][a-z]|-| )*$", "This field exists already or has invalid address");
        break;
    case 5:
        col_name = "convictions";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^[0-9]*$", "This field exists already or invalid");
        break;
    }

    if(isBackuped) return;

    query.exec("UPDATE persons SET " + col_name + " = \'" + ui->TW_persons->item(row, column)->text() + "\' WHERE id = " + QString::number(id));
    qDebug() << "UPDATE persons SET " + col_name + " = \'" + ui->TW_persons->item(row, column)->text() + "\' WHERE id = " + QString::number(id) << query.lastError().databaseText();
}

void MainWindow::on_TW_relations_cellChanged(int row, int column)
{
    if(!isSync) return;

    ///////////TEMPORARY///////////
    static bool isBackuped = false;
    if(isBackuped)
    {
        isBackuped = false;
        return ;
    }
    //////////////////////////////

    QString col_name;
    QSqlQuery query;
    int id = row_to_id(row, "relations");

    switch(column)
    {
    case 0:
        col_name = "incident_id";
        backupField(ui->TW_relations, "relations", col_name, row, column, id, isBackuped, "^[1-9][0-9]*$", "This field exists already or has invalid id");
        break;
    case 1:
        col_name = "registration_id";
        backupField(ui->TW_persons, "persons", col_name, row, column, id, isBackuped, "^[1-9][0-9]*$", "This field exists already or has invalid id");
        break;
    case 2:
        col_name = "relation";
        break;
    }

    if(isBackuped) return;

    query.exec("UPDATE relations SET " + col_name + " = \'" + ui->TW_relations->item(row, column)->text() + "\' WHERE id = " + QString::number(id));
    qDebug() << "UPDATE relations SET " + col_name + " = \'" + ui->TW_relations->item(row, column)->text() + "\' WHERE id = " + QString::number(id) << query.lastError().databaseText();
}

void MainWindow::on_TW_messages_cellClicked(int row, int)
{
    table = "incidents";
    del_id = row_to_id(row, table);
}

void MainWindow::on_TW_persons_cellClicked(int row, int column)
{
    table = "persons";
    del_id = row_to_id(row, table);
}

void MainWindow::on_TW_relations_cellClicked(int row, int column)
{
    table = "relations";
    del_id = row_to_id(row, table);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete adv_opt;
    db.close();
}

void MainWindow::on_TB_tools_clicked()
{
    adv_opt->setWindowModality(Qt::WindowModal);
    adv_opt->show();
}

void MainWindow::on_LE_find_editingFinished()
{
    QTableWidget* wtable = nullptr;
    switch(ui->tabWidget->currentIndex())
    {
    case 0:
        table = "incidents";
        wtable = ui->TW_messages;
        break;
    case 1:
        table = "persons";
        wtable = ui->TW_persons;
        break;
    case 2:
        table = "relations";
        wtable = ui->TW_relations;
        break;
    default:
        return;
    }

    QList<QTableWidgetItem *> res = wtable->findItems(ui->LE_find->text(), Qt::MatchRegularExpression | Qt::MatchCaseSensitive);

    int column = res.first()->column();
    int row = res.first()->row();
    wtable->setCurrentCell(row, column);

}

