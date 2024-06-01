#ifndef MANAGER_H
#define MANAGER_H

#include <QDialog>

namespace Ui {
class Manager;
}

class Manager : public QDialog
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

    void initTable();

private slots:
    void on_PB_2_year_cnt_clicked();
    void on_PB_3_popular_clicked();
    void on_PB_4_info_clicked();
    void on_PB_5_tour_clicked();
    void on_PB_6_price_clicked();

    void on_PB_7_mem_clicked();

private:
    void resizeEvent(QResizeEvent*);

private:
    Ui::Manager *ui;
};

#endif // MANAGER_H
