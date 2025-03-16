#include "chart_view_x.h"
#include <QPieSeries>
#include <QPieSlice>

ChartViewX::ChartViewX(QWidget* parent) : QChartView(parent)
{
}

ChartViewX::~ChartViewX()
{
}

void ChartViewX::mouseMoveEvent(QMouseEvent* event)
{
    QPieSeries* series = static_cast<QPieSeries*>(this->chart()->series().at(0));

    QList<QPieSlice*> slices = series->slices();
    bool exploded = false;
    foreach (QPieSlice* slice, slices) {
        if ( slice->isExploded() ) {
            exploded = true;
            break;
        }
    }

    this->setCursor(exploded ? QCursor(Qt::PointingHandCursor) : QCursor(Qt::ArrowCursor));

    return QChartView::mouseMoveEvent(event);
}
