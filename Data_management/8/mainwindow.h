#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent *);
private slots:
    void on_PB_add_clicked();
    void on_PB_add_coll_clicked();
    void on_PB_add_sec_clicked();
    void on_PB_del_clicked();
    void on_PB_ch_pos_clicked();
    void on_PB_sec_find_country_clicked();
    void on_PB_th_country_clicked();
    void on_PB_find_volume_clicked();
    void on_PB_find_pos_clicked();
    void on_PB_find_theme_clicked();
    void on_PB_pos_find_country_clicked();
    void on_PB_report_clicked();

private:
    Ui::MainWindow *ui;
    class Info* info;
};
#endif // MAINWINDOW_H
