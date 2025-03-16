#ifndef PIESLICEX_H
#define PIESLICEX_H

#include <QPieSlice>
#include <QObject>

using namespace QT_CHARTS_NAMESPACE;
enum LabelStyle { Category = 0x01, Value = 0x02, Percent = 0x04 };

class PieSliceX : public QPieSlice
{
    Q_OBJECT
public:
    explicit PieSliceX(QString category = "", qreal value = 0.0, QObject* parent = nullptr);
    ~PieSliceX();

public slots:
    void onHovered(bool hovered);
    void updateLabel();

public:
    void setBrushColor(QColor normalColor, QColor hoverColor);
    void setPenColor(QColor normalColor, QColor hoverColor);
    void setLabelStyle(LabelStyle style);

    // 外侧可以包含一个series
    void setBreakdownSeries(QPieSeries* series);
    QPieSeries* breakdownSeries();

private:
    QColor getRandomColor();

private:
    QColor normalPenColor;
    QColor hoveredPenColor;

    QColor normalBrushColor;
    QColor hoveredBrushColor;

    QString category;
    LabelStyle labelStyle;

    // 外侧可以包含一个series
    QPieSeries* m_breakdownSeries;
};

#endif  // PIESLICEX_H
