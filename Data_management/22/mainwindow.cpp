#include <QtSql>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shop.h"
#include "salesman.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    shop(new Shop),
    salesman(new Salesman)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../Database/shop");

    if(!db.open()) qFatal() << "Error: database did not open";
}

void MainWindow::closeEvent(QCloseEvent*)
{
    shop->close();
    salesman->close();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete shop;
    delete salesman;
}

void MainWindow::on_PB_shop_clicked()
{
    shop->show();
}

void MainWindow::on_PB_salesman_clicked()
{
    salesman->show();
}

