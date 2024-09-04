#include "tab4chartplot.h"
#include "ui_tab4chartplot.h"

Tab4ChartPlot::Tab4ChartPlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab4ChartPlot)
{
    ui->setupUi(this);
    illuLine = new QLineSeries(this);
    illuLine->setName("조도");

    QPen pen;
    pen.setWidth(2);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    illuLine->setPen(pen);
    chart = new QChart();
//   chart->legend()->hide();
    chart->addSeries(illuLine);

//    chart->setTitle("illumination chart");
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, 100);
//    chart->axes(Qt::Horizontal).first()->setRange(0, 24);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->pChartViewLayout->layout()->addWidget(chartView);

    axisX = new QDateTimeAxis;
//    axisX->setFormat("MM-dd hh:mm");
    axisX->setFormat("hh:mm");

    updateLastDateTime(0);

    chartView->chart()->setAxisX(axisX,illuLine);

    connect(ui->pPBClearButton,SIGNAL(clicked()),this,SLOT(chartPlotClear()));
}
void Tab4ChartPlot::updateLastDateTime(int)
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    firstDate.setDate(date);
    firstDate.setTime(time);

    lastDate.setDate(date);
    QTime tempTime = time.addSecs(60*10);
    lastDate.setTime(tempTime);
    axisX->setRange(firstDate,lastDate);
}

void Tab4ChartPlot::chartPlotClear()
{

    illuLine->clear();
    updateLastDateTime(0);
}

void Tab4ChartPlot::tab4RecvDataSlot(QString recvData)
{

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QDateTime xValue;
    xValue.setDate(date);
    xValue.setTime(time);

    QStringList qlist = recvData.split("@");  //@HM_CON@SENSOR@12.3@4.56@78.9  //조도,온도,습도
    QString illu = qlist[3];        //조도
//    qDebug() << illu;
//    qDebug() << xValue.toMSecsSinceEpoch();
    illuLine->append(xValue.toMSecsSinceEpoch(),illu.toInt());
}

Tab4ChartPlot::~Tab4ChartPlot()
{
    delete ui;
}
