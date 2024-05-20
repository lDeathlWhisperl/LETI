#include <QtSql>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "shop.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    shop(new Shop)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../Database/shop");

    if(!db.open()) qFatal() << "Error: database did not open";
}

void MainWindow::closeEvent(QCloseEvent*)
{
    shop->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PB_shop_clicked()
{
    shop->show();
}

void MainWindow::on_PB_salesman_clicked()
{

}

