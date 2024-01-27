#include "workdone.h"
#include "ui_workdone.h"

WorkDone::WorkDone(QWidget *parent) :
    QWidget(parent), ui(new Ui::WorkDone)
{
    ui->setupUi(this);
}

WorkDone::~WorkDone()
{
    delete ui;
}


void WorkDone::on_PBtn_ok_clicked()
{
    this->hide();
}

