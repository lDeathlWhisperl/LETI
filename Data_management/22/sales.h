#ifndef SALES_H
#define SALES_H

#include <QWidget>

namespace Ui {
class Salesman;
}

class Sales : public QWidget
{
    Q_OBJECT

public:
    explicit Sales(QWidget *parent = nullptr);
    ~Sales();

    void closeEvent(QCloseEvent *);

private slots:
    void on_PB_add_clicked();
    void on_PB_delete_clicked();
    void on_PB_history_clicked();

    void on_PB_salesmen_clicked();

private:
    bool isValid(QString name, double fees, QString sold_item, int sold_amount, QString date);
    bool p_isExist(QString item, int sp);
    bool h_isExist(QString item, int amount, QString date);
    bool s_isExist(QString name, double fees);

    int getId(QString, double, const double award);
    void backupAward(QString name, QString item, int ampunt);

signals:
    void dataChanged();

private:
    Ui::Salesman *ui;

    class historytable* table;
    class Salesmen* salesmen;
};

#endif // SALES_H
