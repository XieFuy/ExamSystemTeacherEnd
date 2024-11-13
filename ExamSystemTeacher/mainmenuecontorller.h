#ifndef CMAINMENUECONTORLLER_H
#define CMAINMENUECONTORLLER_H

#include "mainmenuemodel.h"
#include<vector>
#include<string>
class CMainMenueContorller  //主菜单页面的控制层
{
public:
    CMainMenueContorller();
    ~CMainMenueContorller();
public :
    bool initTeacherInfoTable();
    std::vector<std::vector<std::string>> showTeacherInfo();
private:
    CMainMenueModel* m_mainMenueModel = nullptr;
};

#endif // CMAINMENUECONTORLLER_H
