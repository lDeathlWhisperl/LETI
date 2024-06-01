#include <QtSql>

#include "manager.h"
#include "admin.h"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    manager(new Manager(this)),
    admin(new Admin(this))
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../../groups");

    if(!db.open()) qFatal() << "DB ERROR";
    manager->initTable();
}

void MainWindow::closeEvent(QCloseEvent*)
{
    manager->close();
    admin->close();
}

void MainWindow::on_PB_manager_clicked()
{
    manager->show();
}

void MainWindow::on_PB_admin_clicked()
{
    admin->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete admin;
}
