#ifndef REPORT_H
#define REPORT_H

#include <QDialog>

namespace Ui {
class Report;
}

class Report : public QDialog
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

    void generate(const QString&);

private:
    Ui::Report *ui;
};

#endif // REPORT_H
