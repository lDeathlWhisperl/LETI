#ifndef SALESMEN_H
#define SALESMEN_H

#include <QDialog>

namespace Ui {
class Salesmen;
}

class Salesmen : public QDialog
{
    Q_OBJECT

public:
    explicit Salesmen(QWidget *parent = nullptr);
    ~Salesmen();

private:
    void resizeEvent(QResizeEvent *);
    bool isValid(QString name, double fees, int id);

public slots:
    void updateEntries();

private slots:
    void on_PB_hire_clicked();
    void on_PB_fire_clicked();

signals:
    void dataChanged();

private:
    Ui::Salesmen *ui;
};

#endif // SALESMEN_H
