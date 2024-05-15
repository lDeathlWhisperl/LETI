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
    Ui::Advanced *ui;
};

#endif // ADVANCED_H
