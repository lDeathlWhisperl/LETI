#ifndef SALESMAN_H
#define SALESMAN_H

#include <QWidget>

namespace Ui {
class Salesman;
}

class Salesman : public QWidget
{
    Q_OBJECT

public:
    explicit Salesman(QWidget *parent = nullptr);
    ~Salesman();

private slots:
    void on_PB_add_clicked();

    void on_PB_delete_clicked();

    void on_PB_history_clicked();

private:
    bool isValid(QString name, double fees, QString sold_item, int sold_amount, QString date);
    bool isExist(QString item, int sp);

private:
    Ui::Salesman *ui;
};

#endif // SALESMAN_H
