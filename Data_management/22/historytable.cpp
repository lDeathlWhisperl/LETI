#include <QtSql>

#include "historytable.h"
#include "ui_historytable.h"
#include "sales.h"

historytable::historytable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::historytable)
{
    ui->setupUi(this);

    prnt = static_cast<Sales*>(parent);
    if(!prnt) qFatal() << "Something went wrong";

    connect(prnt, SIGNAL(dataChanged()), this, SLOT(updateEntries()));
}

void historytable::resizeEvent(QResizeEvent*)
{
    for(int i = 0; i < 4; ++i)
        ui->TW_history->setColumnWidth(i, ui->TW_history->geometry().width() / 4);
}

void historytable::updateEntries()
{
    ui->TW_history->setRowCount(0);

    QSqlQuery query, q;

    query.exec("SELECT * FROM history");
    while(query.next())
    {
        ui->TW_history->insertRow(ui->TW_history->rowCount());
        for(int i = 2; i <= 4; ++i)
        {
            q.exec("SELECT name FROM salesmen WHERE id = " + query.value(1).toString());

            if(q.next())
                ui->TW_history->setItem(ui->TW_history->rowCount()-1, 0, new QTableWidgetItem(q.value(0).toString()));
            ui->TW_history->setItem(ui->TW_history->rowCount()-1, i-1, new QTableWidgetItem(query.value(i).toString()));
        }
    }
}

historytable::~historytable()
{
    delete ui;
}
