#ifndef SHOP_H
#define SHOP_H

#include <QWidget>

namespace Ui {
class Shop;
}

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();

private:
    bool isExists(QString, int, int = -1, int = -1);
    void updateProduct(QString name, int);
    bool isValid(QString name, QString unit, QString pp = "0", QString sp = "0");

    void closeEvent(QCloseEvent*);

private slots:
    void on_PB_addToBD_clicked();
    void on_PB_removeFromBD_clicked();
    void on_PB_getAllProducts_clicked();

signals:
    void dataChanged();

private:
    Ui::Shop *ui;
    class ProductTable* table;
};

#endif // SHOP_H
