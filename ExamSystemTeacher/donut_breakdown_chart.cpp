#include "donut_breakdown_chart.h"
#include <QLegendMarker>
#include <QPieLegendMarker>
#include "pie_slice_x.h"

DonutBreakdownChart::DonutBreakdownChart()
{
}

void DonutBreakdownChart::addBreakdownSeries(QPieSeries* series)
{
    this->addSeries(series);

    // 自定义图例的样式
    QList<QLegendMarker*> markers = this->legend()->markers(series);
    for ( QLegendMarker* marker : markers ) {
        QPieLegendMarker* pieMarker = static_cast<QPieLegendMarker*>(marker);
        QString label = pieMarker->slice()->label();
        qreal percent = pieMarker->slice()->percentage();
        pieMarker->setLabel(QString("%1 %2%").arg(label).arg(percent * 100, 0, 'f', 2));
    }

    recalculateAngles();
}

void DonutBreakdownChart::addMainSeries(QPieSeries* series)
{
    this->addSeries(series);
    this->mainSeries = series;

    // 隐藏图例
    QList<QLegendMarker*> markers = this->legend()->markers(mainSeries);
    for ( QLegendMarker* marker : markers ) {
        marker->setVisible(false);
    }
}

void DonutBreakdownChart::recalculateAngles()
{
    qreal angle = 0;
    const auto slices = mainSeries->slices();
    for ( QPieSlice* slice : slices ) {
        QPieSeries* breakdownSeries = static_cast<PieSliceX*>(slice)->breakdownSeries();
        breakdownSeries->setPieStartAngle(angle);
        angle += slice->percentage() * 360.0;
        breakdownSeries->setPieEndAngle(angle);
    }
}
