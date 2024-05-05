#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startTimer(100);
}

void MainWindow::timerEvent(QTimerEvent*)
{
    getData();
    updateStat();
}

void MainWindow::getData()
{
    cashier_count = ui->LE_N->text().toInt();
    max_queue = ui->LE_M->text().toInt();
}

void MainWindow::updateStat()
{
    ui->L_maxQueue->setText(QString::number(cashier_count * max_queue));
    ui->L_totalCashier->setText(QString::number(cashier_count));
    ui->L_totalOrder->setText(QString::number(totalOrder));
    ui->L_queue->setText(QString::number(queue));
}

void MainWindow::on_PB_queue_clicked()
{
    if(queue == cashier_count * max_queue) return;
    ++queue;
}

void MainWindow::on_PB_order_clicked()
{
    if(queue == 0) return;

    --queue;
    ++totalOrder;
    ui->L_totalOrder->setText(QString::number(totalOrder));
}

MainWindow::~MainWindow()
{
    delete ui;
}
