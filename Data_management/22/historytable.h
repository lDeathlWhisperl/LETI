#ifndef HISTORYTABLE_H
#define HISTORYTABLE_H

#include <QDialog>

namespace Ui {
class historytable;
}

class historytable : public QDialog
{
    Q_OBJECT

public:
    explicit historytable(QWidget *parent = nullptr);
    ~historytable();

private:
    void resizeEvent(QResizeEvent *);

public slots:
    void updateEntries();

private:
    Ui::historytable *ui;

    class Salesman* prnt;
};

#endif // HISTORYTABLE_H
