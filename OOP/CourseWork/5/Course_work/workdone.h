#ifndef WORKDONE_H
#define WORKDONE_H

#include <QWidget>

namespace Ui {
class WorkDone;
}

class WorkDone : public QWidget
{
    Q_OBJECT

public:
    explicit WorkDone(QWidget *parent = nullptr);
    ~WorkDone();

private slots:
    void on_PBtn_ok_clicked();

private:
    Ui::WorkDone *ui;
};

#endif // WORKDONE_H
