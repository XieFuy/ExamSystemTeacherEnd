#ifndef BARWIDGET_H
#define BARWIDGET_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>

class BarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BarWidget(QWidget* parent = nullptr);

signals:

private:
    void addBars();

private:
    QScrollArea* scrollArea;
    QGridLayout* gridLayout;
};

#endif  // BARWIDGET_H
