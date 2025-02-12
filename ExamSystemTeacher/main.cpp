#include "widget.h"

#include <QApplication>
#if  defined(Q_OS_WIN)
#include "dpihelper.h"
#include<windows.h>
#include<wingdi.h>
#include<winuser.h>
#include<QScreen>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
#endif

class ScreenInfo{  //进行设置分辨率和缩放来保证软件的布局和文字显示正常
public:
    ScreenInfo();
    ~ScreenInfo();
    void setScreenSize(int width,int heigth); //设置当前显示屏幕的分辨率
    void getScreenSize(int& width,int& height);//获取当前显示屏幕的分辨率以及缩放比例
private:
    int m_screenWidth;
    int m_screenHeigth;
};

ScreenInfo::ScreenInfo():m_screenWidth(0),m_screenHeigth(0){
    //先进行获取当前屏幕的分辨率
    this->getScreenSize(this->m_screenWidth,this->m_screenHeigth);
    //进行设置分辨率为1920 * 1080
    this->setScreenSize(1920,1080);
}

ScreenInfo::~ScreenInfo(){
    this->setScreenSize(this->m_screenWidth,this->m_screenHeigth); //将屏幕尺寸分辨率设置为原来的分辨率
    qDebug()<<"ScreenInfo 释放！";
}

void ScreenInfo::setScreenSize(int width,int heigth)
{
    // 定义DEVMODE结构体来设置新的显示模式
    DEVMODE DevMode; //屏幕信息结构体
    EnumDisplaySettings(NULL,ENUM_CURRENT_SETTINGS,&DevMode); //获取当前的数据
    DevMode.dmPelsWidth = width; //修改成你想要的分辨率
    DevMode.dmPelsHeight = heigth;
    if(ChangeDisplaySettings(&DevMode, CDS_UPDATEREGISTRY) == DISP_CHANGE_SUCCESSFUL)//设置生效
    {
        qDebug()<<"设置成功！";
    }
}

void ScreenInfo::getScreenSize(int& width,int& height)
{
    HDC hDC = ::GetDC(NULL); //进行获取整个屏幕的DC
    width = ::GetDeviceCaps(hDC, HORZRES);
    height = ::GetDeviceCaps(hDC, VERTRES);
    ReleaseDC(NULL, hDC); // 释放DC
    qDebug()<<"width: "<<width<<"this->width: "<<this->m_screenWidth
           <<"height: "<<height<<"this->heigth: "<<this->m_screenHeigth;
}

int main(int argc, char *argv[])
{
    std::shared_ptr<DpiHelper> dpiHelper = std::make_shared<DpiHelper>();
    //申请管理员权限
    if (!dpiHelper->isRunningAsAdmin()) {
            if (dpiHelper->requestAdminRights()) {
                return 0; // 退出当前实例，等待管理员权限实例启动
            } else {
                return -1; // 退出程序
            }
    }

    //进行获取当前dpi
    // 获取当前缩放比例
    int currentScaling =dpiHelper->GetCurrentScalingPercentage();
    dpiHelper->localScaling = currentScaling;

    //设置缩放比例为125%
    int targetScaling = 125;
     if (dpiHelper->SetScalingPercentage(targetScaling)) {
        qDebug()<< "Scaling percentage set to " << targetScaling << "%";
     } else {
        qDebug()<< "Failed to set scaling percentage.";
     }

    std::shared_ptr<ScreenInfo> sInfo = std::make_shared<ScreenInfo>();
    /******************上部分的代码是设置dpi的代码***********************/
    QApplication a(argc, argv);
    Widget w;
    w.show();
    int ret =  a.exec();
    dpiHelper.reset();
    sInfo.reset();
    return ret;
}
