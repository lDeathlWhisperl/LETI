#include <QtSql>

#include "historytable.h"
#include "ui_historytable.h"
#include "salesman.h"

historytable::historytable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::historytable)
{
    ui->setupUi(this);

    prnt = static_cast<Salesman*>(parent);
    if(!prnt) qFatal() << "Something went wrong";

    connect(prnt, SIGNAL(dataChanged()), this, SLOT(updateEntries()));
}

void historytable::resizeEvent(QResizeEvent*)
{
    for(int i = 0; i < 6; ++i)
        ui->TW_history->setColumnWidth(i, ui->TW_history->geometry().width() / 6);
}

void historytable::updateEntries()
{
    ui->TW_history->setRowCount(0);

    QSqlQuery query, q;


    query.exec("SELECT * FROM history");
    while(query.next())
    {
        ui->TW_history->insertRow(ui->TW_history->rowCount());
        for(int i = 1; i < 4; ++i)
        {
            q.exec("SELECT * FROM salesmen WHERE id = " + query.value(0).toString());

            if(q.next())
            {
                ui->TW_history->setItem(ui->TW_history->rowCount()-1, 0, new QTableWidgetItem(q.value(1).toString()));
                ui->TW_history->setItem(ui->TW_history->rowCount()-1, 1, new QTableWidgetItem(q.value(2).toString()));
                ui->TW_history->setItem(ui->TW_history->rowCount()-1, 2, new QTableWidgetItem(q.value(3).toString()));
            }
            ui->TW_history->setItem(ui->TW_history->rowCount()-1, i+2, new QTableWidgetItem(query.value(i).toString()));
        }
    }
}

historytable::~historytable()
{
    delete ui;
}
