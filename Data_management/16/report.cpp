#include <QtSql>

#include "report.h"
#include "ui_report.h"

Report::Report(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Report)
{
    ui->setupUi(this);
}

void Report::generate()
{
    QSqlQuery query("SELECT id, name "
                    "FROM groups "
                    "ORDER BY hit_parade ASC");
    QString report = "Топ 3 групп хит-парада:\n";
    QMap<int, QString> group;

    for(int i = 1; i <= 3, query.next(); ++i)
    {
        group[query.value(0).toInt()] = query.value(1).toString();
        report += QString::number(i) + ". " + query.value(1).toString() + "\n";
    }

    report += "\nТуры:\n";
    for(const auto& [k, v] : group.asKeyValueRange())
    {
        report += v + ": \n";
        query.exec("SELECT name, date_start, date_end "
                   "FROM tour "
                   "WHERE group_id = " + QString::number(k));

        while(query.next())
            report += " > " + query.value(0).toString() + ": " + query.value(1).toString() + " - " + query.value(2).toString() + "\n";
    }

    report += "\n\nРепертуар:\n";
    for(const auto& [k, v] : group.asKeyValueRange())
    {
        report += v + ": \n";
        query.exec("SELECT name, autor "
                   "FROM song "
                   "WHERE group_id = " + QString::number(k));

        while(query.next())
            report += " > " + query.value(0).toString() + " - " + query.value(1).toString() + "\n";
    }

    ui->L_report->setText(report);
}

Report::~Report()
{
    delete ui;
}
