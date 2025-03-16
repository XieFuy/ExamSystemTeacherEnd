#ifndef CHARTVIEWX_H
#define CHARTVIEWX_H

#include <QChartView>
#include <QWidget>

using namespace QT_CHARTS_NAMESPACE;

class ChartViewX : public QChartView
{
    Q_OBJECT
public:
    ChartViewX(QWidget* parent = nullptr);
    ~ChartViewX();

protected:
    void mouseMoveEvent(QMouseEvent* event);
};

#endif  // CHARTVIEWX_H
