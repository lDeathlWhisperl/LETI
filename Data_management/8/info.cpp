#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Info)
{
    ui->setupUi(this);

}

void Info::setText(QString text)
{
    ui->L_text->setText(text);
}

Info::~Info()
{
    delete ui;
}
