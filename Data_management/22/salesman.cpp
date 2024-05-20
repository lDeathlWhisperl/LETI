#include "salesman.h"
#include "ui_salesman.h"

Salesman::Salesman(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Salesman)
{
    ui->setupUi(this);
}

Salesman::~Salesman()
{
    delete ui;
}
