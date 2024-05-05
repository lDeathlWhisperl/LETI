#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PB_queue_clicked();

    void on_PB_order_clicked();

private:
    virtual void timerEvent(QTimerEvent*);

    void getData();
    void updateStat();

private:
    Ui::MainWindow *ui;

    uint32_t max_queue = 0;
    uint32_t cashier_count = 0;
    uint32_t queue = 0;
    uint32_t totalOrder = 0;
};
#endif // MAINWINDOW_H
