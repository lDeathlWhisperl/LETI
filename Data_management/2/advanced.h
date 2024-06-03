#ifndef ADVANCED_H
#define ADVANCED_H

#include <QDialog>

namespace Ui {
class Advanced;
}

class Advanced : public QDialog
{
    Q_OBJECT

public:
    explicit Advanced(QWidget *parent = nullptr);
    ~Advanced();

private:

private slots:
    void on_LE_date_s_editingFinished();
    void on_LE_date_e_editingFinished();
    void getIncidentsCount();

    void on_LE_reg_id_editingFinished();

    void on_PB_get_protocol_clicked();

signals:
    void dateChanged();

private:
    Ui::Advanced *ui;

    QString date_start;
    QString date_end;

    class QRegularExpression* re;
    class Report* report;
};

#endif // ADVANCED_H
