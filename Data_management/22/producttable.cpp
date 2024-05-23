#include <QtSql>

#include "shop.h"

#include "producttable.h"
#include "ui_producttable.h"

ProductTable* ProductTable::instance;

ProductTable::ProductTable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProductTable)
{
    ui->setupUi(this);

    auto prnt = static_cast<Shop*>(parent);
    if(!prnt) qFatal() << "Something went wrong...";

    connect(prnt, SIGNAL(dataChanged()), this, SLOT(updateEntries()));
}

void ProductTable::resizeEvent(QResizeEvent*)
{
    for(int i = 0; i < 4; ++i)
        ui->TW_products->setColumnWidth(i, ui->TW_products->geometry().width() / 4);
}

void ProductTable::updateEntries()
{
    QSqlQuery query;
    query.exec("SELECT * FROM product");

    ui->TW_products->setRowCount(0);
    while(query.next())
    {
        ui->TW_products->insertRow(ui->TW_products->rowCount());
        for(int i = 1; i < 5; ++i)
            ui->TW_products->setItem(ui->TW_products->rowCount()-1, i-1, new QTableWidgetItem(query.value(i).toString()));
    }
}

ProductTable::~ProductTable()
{
    delete ui;
}
