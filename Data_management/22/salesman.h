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

private:
    Ui::Salesman *ui;
};

#endif // SALESMAN_H
