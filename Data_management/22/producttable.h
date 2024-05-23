#ifndef PRODUCTTABLE_H
#define PRODUCTTABLE_H

#include <QDialog>

namespace Ui {
class ProductTable;
}

class ProductTable : public QDialog
{
    Q_OBJECT

    static ProductTable* instance;

    explicit ProductTable(QWidget *parent = nullptr);
public:
    ~ProductTable();

    static ProductTable* getInstance(QWidget *parent = nullptr)
    {
        if(!instance)
            instance = new ProductTable(parent);

        return instance;
    }

private:
    void resizeEvent(QResizeEvent*);

public slots:
    void updateEntries();

private:
    Ui::ProductTable *ui;
};

#endif // PRODUCTTABLE_H
