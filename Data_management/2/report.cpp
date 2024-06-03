#include <QtSql>

#include "report.h"
#include "ui_report.h"

Report::Report(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Report)
{
    ui->setupUi(this);
}

void Report::generate(const QString& num)
{
#define DATA(id) query.value(id).toString()

    QSqlQuery query;
    query.exec("SELECT criminal_id, relation, name, surname, patronymic, persons.registration_id, address, convictions, date, type, conclusion "
               "FROM relations "
               "INNER JOIN persons ON persons.registration_id = relations.registration_id "
               "INNER JOIN incidents on incident_id = message_id "
               "WHERE message_id = " + num);
    qDebug() << "SELECT criminal_id, relation, name, surname, patronymic, persons.registration_id, address, convictions, date, type, conclusion "
                "FROM relations "
                "INNER JOIN persons ON persons.registration_id = relations.registration_id "
                "INNER JOIN incidents on incident_id = message_id "
                "WHERE message_id = " + num << query.lastError().text();

    if(query.first())
    {
        QString report = "По сообщению №" + num + " составлено уголовное дело №" + DATA(0) + "\n" +
                         DATA(1) + ": " + DATA(2) + " " + DATA(3) + " " + DATA(4) + ", регистрационный номер: " + DATA(5) + "\n" +
                         "Проживающий по адресу: " + DATA(6) + "\n" +
                         "Количество судимостей: " + DATA(7) + "\n" +
                         DATA(8) + "го совершил " + DATA(9) + "\n" +
                         "Решение по делу: " + DATA(10);

        ui->L_text->setText(report);
    }
}

Report::~Report()
{
    delete ui;
}
