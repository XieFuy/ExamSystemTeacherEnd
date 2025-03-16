#include "bar_widget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QChartView>
#include <QBarSeries>
#include <qbarset>
#include <QLegend>
#include <QBarCategoryAxis>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

BarWidget::BarWidget(QWidget* parent) : QWidget{parent}
{
    this->setStyleSheet("background-color: rgb(220,240,255)");

    // 整体采用垂直布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 使用 QScrollArea 可以按需显示滚动条
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* scrollAreaContent = new QWidget(this);
    gridLayout = new QGridLayout(scrollAreaContent);
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(5, 5, 5, 5);

    scrollArea->setWidget(scrollAreaContent);

    mainLayout->addWidget(scrollArea);

    addBars();
}

void BarWidget::addBars()
{
    // 1. 创建QBarSet  给图标的数据集
    QBarSet* set = new QBarSet("年销量");
    *set << 15 << 65 << 19 << 57 << 43 << 68 << 88 << 45 << 77 << 33;
    set->setBrush(QBrush(QColor(230, 100, 100)));

    // 2. 创建QBarSeries
    QBarSeries* series = new QBarSeries();
    series->append(set);
    series->setBarWidth(0.75);  // 设置柱子的宽度。默认值是0.5

    // 3. 创建QChart
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("总分区间人数榜");
    chart->setTitleFont(QFont("Microsoft YaHei", 16, QFont::Bold));
    chart->setTitleBrush(QColor(255, 255, 255));

    // 设置动画。设置为SeriesAnimations比AllAnimations效果更好一点
    //    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // 设置QChart的背景色为渐变色
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(50, 100, 150));
    gradient.setColorAt(1, QColor(0, 50, 100));
    chart->setBackgroundBrush(gradient);

    // 4. 设置QBarCategoryAxis轴
    QStringList categories;
    categories << "0~10分"
               << "10~20分"
               << "20~30分"
               << "30~40分"
               << "40~50分"
               << "50~60分"
               << "60~70分"
               << "70~80分"
               << "80~90分"
               << "90~100分";

    QBarCategoryAxis* categoryAxis = new QBarCategoryAxis();
    categoryAxis->setTitleVisible(false);                                   // 显示标题
    categoryAxis->setTitleText("分数区间");                                     // 标题
    categoryAxis->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));  // 标题字体
    categoryAxis->setTitleBrush(QColor(255, 255, 255));                     // 标题颜色

    categoryAxis->append(categories);
    categoryAxis->setGridLineVisible(false);  // 隐藏网格线
    categoryAxis->setLabelsColor(QColor(255, 255, 255));
    categoryAxis->setLabelsFont(QFont("Microsoft YaHei", 12));

    chart->addAxis(categoryAxis, Qt::AlignBottom);
    series->attachAxis(categoryAxis);

    // 5. 设置QValueAxis轴
    QValueAxis* valueAxis = new QValueAxis();
    valueAxis->setTitleVisible(true);
    valueAxis->setTitleText("人数(单位:个)");
    valueAxis->setTitleFont(QFont("Microsoft YaHei", 14, QFont::Bold));  // 标题字体
    valueAxis->setTitleBrush(QColor(255, 255, 255));                     // 标题颜色

    valueAxis->setRange(0, 100); //这里进行修改y轴的总范围
    valueAxis->setLabelFormat("%d");      // 支持printf()的格式
    valueAxis->setGridLineVisible(true);  // 默认就是显示网格线
    valueAxis->setGridLineColor(QColor(130, 130, 130));
    valueAxis->setLabelsColor(QColor(255, 255, 255));
    valueAxis->setLabelsFont(QFont("Microsoft YaHei", 12));

    chart->addAxis(valueAxis, Qt::AlignLeft);
    series->attachAxis(valueAxis);

    // 显示数值
    series->setLabelsVisible(true);                           // 是否显示数值
    series->setLabelsPosition(QBarSeries::LabelsOutsideEnd);  // 位置
    series->setLabelsAngle(0);                                // 旋转角度。默认值0

    // 6. 设置图例
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignTop);
    chart->legend()->setFont(QFont("Microsot YaHei"));

    // 7. 创建QChartView
    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumWidth(900);

    gridLayout->addWidget(chartView, 0, 0);
}
