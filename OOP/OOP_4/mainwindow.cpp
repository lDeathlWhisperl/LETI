#include "mainwindow.h"
#include "Polynom.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    polynom = new Polynom();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete polynom;
}


void MainWindow::on_Btn_A_clicked()
{
    number a(ui->LE_A_1->text().toDouble(), ui->LE_A_2->text().toDouble());
    number b(ui->LE_B_1->text().toDouble(), ui->LE_B_2->text().toDouble());
    number c(ui->LE_C_1->text().toDouble(), ui->LE_C_2->text().toDouble());

    polynom->setA(a);
    polynom->setB(b);
    polynom->setC(c);

    QString str;
    str << *polynom;
    ui->L_Equation->setText(str);
    ui->L_X->setText("");
    ui->L_Solvation->setText("");
}


void MainWindow::on_Btn_B_clicked()
{
    on_Btn_A_clicked();
}


void MainWindow::on_Btn_C_clicked()
{
    on_Btn_A_clicked();
}


void MainWindow::on_Btn_Solve_clicked()
{
    ui->L_Solvation->setText(polynom->solve());
}


void MainWindow::on_Btn_X_clicked()
{
    QString str;
    str << polynom->solve(number(ui->LE_X_1->text().toDouble(), ui->LE_X_2->text().toDouble()));
    ui->L_X->setText(str);
}


void MainWindow::LE_setHidden(QLineEdit* LE_Widget_1, QLineEdit* LE_Widget_2, bool isHidden, QString placeHolderText = "")
{
    LE_Widget_1->setPlaceholderText(placeHolderText);
    LE_Widget_2->setHidden(isHidden);
    LE_Widget_2->clear();
    on_Btn_A_clicked();
}


void MainWindow::on_CB_Complex_stateChanged(int arg1)
{
    if(!ui->CB_Complex->isChecked())
    {
        LE_setHidden(ui->LE_A_1, ui->LE_A_2, true);
        LE_setHidden(ui->LE_B_1, ui->LE_B_2, true);
        LE_setHidden(ui->LE_C_1, ui->LE_C_2, true);
        LE_setHidden(ui->LE_X_1, ui->LE_X_2, true);
    }
    else
    {
        LE_setHidden(ui->LE_A_1, ui->LE_A_2, false, "Re");
        LE_setHidden(ui->LE_B_1, ui->LE_B_2, false, "Re");
        LE_setHidden(ui->LE_C_1, ui->LE_C_2, false, "Re");
        LE_setHidden(ui->LE_X_1, ui->LE_X_2, false, "Re");
    }
}
