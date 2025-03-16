#ifndef DONUTBREAKDOWNCHART_H
#define DONUTBREAKDOWNCHART_H

#include <QChart>
#include <QObject>
#include <QPieSeries>

using namespace QT_CHARTS_NAMESPACE;

class DonutBreakdownChart : public QChart
{
    Q_OBJECT
public:
    DonutBreakdownChart();

    void addBreakdownSeries(QPieSeries* series);
    void addMainSeries(QPieSeries* series);

private:
    void recalculateAngles();

private:
    QPieSeries* mainSeries;
};

#endif  // DONUTBREAKDOWNCHART_H
