#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>

namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr);
    ~Admin();

private slots:
    void on_PB_add_group_clicked();
    void on_PB_add_song_clicked();
    void on_PB_add_tour_clicked();
    void on_PB_ch1_clicked();
    void on_PB_ch2_clicked();

private:
    Ui::Admin *ui;
};

#endif // ADMIN_H
