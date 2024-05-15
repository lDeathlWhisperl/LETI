#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

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

private slots:
    void on_TW_messages_cellChanged(int row, int column);
    void on_TW_messages_cellClicked(int row, int column);
    void on_PB_m_entry_clicked();

    void on_TW_persons_cellClicked(int row, int column);
    void on_TW_persons_cellChanged(int row, int column);
    void on_PB_p_entry_clicked();

    void on_TW_relations_cellClicked(int row, int column);
    void on_TW_relations_cellChanged(int row, int column);
    void on_PB_r_entry_clicked();

    void on_TB_tools_clicked();


    void on_LE_find_editingFinished();

private:
    void resizeEvent(QResizeEvent*);
    void keyPressEvent(QKeyEvent*);
    void sync();

private:
    Ui::MainWindow *ui;
    class Advanced *adv_opt;

    QSqlDatabase db;
    bool isSync = false;

    int del_id = -1;
    QString table;
};
#endif // MAINWINDOW_H
