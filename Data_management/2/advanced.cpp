#include "advanced.h"
#include "ui_advanced.h"

Advanced::Advanced(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Advanced)
{
    ui->setupUi(this);
}

Advanced::~Advanced()
{
    delete ui;
}
