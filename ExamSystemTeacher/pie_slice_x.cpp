#include "pie_slice_x.h"
#include <QRandomGenerator>

PieSliceX::PieSliceX(QString category, qreal value, QObject* parent) : QPieSlice{parent}
{
    // 设置label 和 label 样式
    labelStyle = LabelStyle::Category;
    this->category = category;
    this->setLabel(category);

    // 设置value
    this->setValue(value);

    // 设置画刷颜色
    QColor brushColor = getRandomColor();
    this->setBrushColor(brushColor, brushColor.lighter());

    // 设置画笔颜色
    setPenColor(QColor(255, 255, 255), QColor(255, 255, 255));

    // 设置凸起因子
    setExplodeDistanceFactor(0.04);

    connect(this, &PieSliceX::hovered, this, &PieSliceX::onHovered);
    connect(this, &PieSliceX::percentageChanged, this, &PieSliceX::updateLabel);
}

PieSliceX::~PieSliceX()
{
}

void PieSliceX::onHovered(bool hovered)
{
    // 画笔
    QPen pen = this->pen();
    pen.setColor(hovered ? hoveredPenColor : normalPenColor);
    this->setPen(pen);

    // 画刷
    QBrush brush = this->brush();
    brush.setColor(hovered ? hoveredBrushColor : normalBrushColor);
    this->setBrush(brush);

    // 凸起
    this->setExploded(hovered);

    // label 字体加粗
    QFont font = this->labelFont();
    font.setBold(hovered);
    this->setLabelFont(font);
}

void PieSliceX::updateLabel()
{
    QString label = "";

    if ( this->labelStyle & 0x01 ) {
        label += this->category;
        if ( this->labelStyle & 0x02 ) {
            label += " ";
            label += QString::number(this->value());
            if ( this->labelStyle & 0x04 ) {
                label += " ";
                label += QString::number(this->percentage() * 100, 'f', 1);
                label += "%";
            }
        } else {
            if ( this->labelStyle & 0x04 ) {
                label += " ";
                label += QString::number(this->percentage() * 100, 'f', 1);
                label += "%";
            }
        }
    } else {
        if ( this->labelStyle & 0x02 ) {
            label += " ";
            label += QString::number(this->value());
            if ( this->labelStyle & 0x04 ) {
                label += " ";
                label += QString::number(this->percentage() * 100, 'f', 1);
                label += "%";
            }
        } else {
            if ( this->labelStyle & 0x04 ) {
                label += " ";
                label += QString::number(this->percentage() * 100, 'f', 1);
                label += "%";
            }
        }
    }

    this->setLabel(label);
}

void PieSliceX::setBrushColor(QColor normalColor, QColor hoverColor)
{
    normalBrushColor = normalColor;
    hoveredBrushColor = hoverColor;

    QBrush brush = this->brush();
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(normalBrushColor);
    this->setBrush(brush);
}

void PieSliceX::setPenColor(QColor normalColor, QColor hoverColor)
{
    normalPenColor = normalColor;
    hoveredPenColor = hoverColor;

    QPen pen = this->pen();
    pen.setColor(normalPenColor);
    this->setPen(pen);
}

void PieSliceX::setLabelStyle(LabelStyle style)
{
    this->labelStyle = style;
}

void PieSliceX::setBreakdownSeries(QPieSeries* series)
{
    m_breakdownSeries = series;
}

QPieSeries* PieSliceX::breakdownSeries()
{
    return m_breakdownSeries;
}

QColor PieSliceX::getRandomColor()
{
    int r = QRandomGenerator::global()->generate() % 235;
    int g = QRandomGenerator::global()->generate() % 235;
    int b = QRandomGenerator::global()->generate() % 235;

    return QColor(r, g, b);
}
