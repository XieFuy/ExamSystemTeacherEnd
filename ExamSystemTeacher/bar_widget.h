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
    void setValue(int& zoreToTen,int& TenToTwoty,int& twotyToThirty
                  ,int& thirtyToForty,int& fourtyToFifty,int& FiftyToSixty,
                  int& SixtyToSeventy,int& seventyToEighty,int& EightToNighty,
                  int& nightyToHunder);
signals:
void startShowUI();
private:
    void addBars();
    //各区间中的人数
    int zoreToTen;
    int TenToTwoty;
    int twotyToThirty;
    int thirtyToForty;
    int fourtyToFifty;
    int FiftyToSixty;
    int SixtyToSeventy;
    int seventyToEighty;
    int EightToNighty;
    int nightyToHunder;
private:
    QScrollArea* scrollArea;
    QGridLayout* gridLayout;
};

#endif  // BARWIDGET_H
