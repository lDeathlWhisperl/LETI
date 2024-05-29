#include <QtSql>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shop.h"
#include "sales.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    shop(new Shop),
    sales(new Sales)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../Database/shop");

    if(!db.open()) qFatal() << "Error: database did not open";

    connect(shop, SIGNAL(dataChanged()), this, SLOT(profit()));
    connect(sales, SIGNAL(dataChanged()), this, SLOT(profit()));
    profit();
}

void MainWindow::profit()
{
    QSqlQuery query;
    query.exec("SELECT SUM(prdct_prft) "
               "FROM (SELECT (sale_price - purchase_price) * unit AS prdct_prft "
                     "FROM product)");

    if(query.next())
        ui->L_predict_profit->setText("Ожидаемая прибыль: " + query.value(0).toString());

    query.exec("SELECT SUM(profit)"
               "FROM (SELECT (sale_price - purchase_price) * sold_amount AS profit "
                     "FROM history, product "
                     "WHERE sold_item = name)");

    if(query.next())
        ui->L_profit->setText("Фактическая прибыль: " + query.value(0).toString());
}

void MainWindow::closeEvent(QCloseEvent*)
{
    shop->close();
    sales->close();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shop;
    delete sales;
}

void MainWindow::on_PB_shop_clicked()
{
    shop->show();
}

void MainWindow::on_PB_salesman_clicked()
{
    sales->show();
}

