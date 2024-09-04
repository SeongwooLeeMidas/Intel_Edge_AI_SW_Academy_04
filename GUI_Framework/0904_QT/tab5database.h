#ifndef TAB5DATABASE_H
#define TAB5DATABASE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QLineSeries>
#include <QChartView>
#include <QDebug>
#include <QDateTimeAxis>

QT_CHARTS_USE_NAMESPACE
namespace Ui {
class Tab5Database;
}

class Tab5Database : public QWidget
{
    Q_OBJECT

public:
    explicit Tab5Database(QWidget *parent = nullptr);
    ~Tab5Database();

private:
    Ui::Tab5Database *ui;
    QSqlDatabase qSqlDatabase;
    QLineSeries* illuLine;
    QChart *chart = nullptr;
    QChartView *chartView = nullptr;
    QDateTimeAxis * axisX;
    QDateTime firstDate;
    QDateTime lastDate;

    void updateLastDateTime(int);
    void updateLastDateTimeSql(int);
private slots:
    void tab5RecvDataSlot(QString);
    void searchDbSlot();
    void deleteDbSlot();

};

#endif // TAB5DATABASE_H
