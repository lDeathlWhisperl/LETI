#ifndef PRODUCTTABLE_H
#define PRODUCTTABLE_H

#include <QDialog>

namespace Ui {
class ProductTable;
}

class ProductTable : public QDialog
{
    Q_OBJECT

public:
    explicit ProductTable(QWidget *parent = nullptr);
    ~ProductTable();

private:
    void resizeEvent(QResizeEvent*);

public slots:
    void updateEntries();

private:
    Ui::ProductTable *ui;
};

#endif // PRODUCTTABLE_H
