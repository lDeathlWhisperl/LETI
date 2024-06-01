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
    void closeEvent(QCloseEvent*);

private slots:
    void on_PB_manager_clicked();
    void on_PB_admin_clicked();

    void on_PB_report_clicked();

private:
    Ui::MainWindow *ui;

    class Manager* manager;
    class Admin* admin;
    class Report* report;
};
#endif // MAINWINDOW_H
