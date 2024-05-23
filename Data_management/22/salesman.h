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

    void closeEvent(QCloseEvent *);

private slots:
    void on_PB_add_clicked();
    void on_PB_delete_clicked();
    void on_PB_history_clicked();

private:
    bool isValid(QString name, double fees, QString sold_item, int sold_amount, QString date);
    bool isExist(QString item, int sp);
    bool isExist(QString item, int amount, QString date);

    int getId(QString, double, double award);

signals:
    void dataChanged();

private:
    Ui::Salesman *ui;

    class historytable* table;
};

#endif // SALESMAN_H
