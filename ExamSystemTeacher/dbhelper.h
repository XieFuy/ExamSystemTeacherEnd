#ifndef DBHELPER_H
#define DBHELPER_H

#include<mysql.h>
#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
//云服务器上的数据库要设置安全组开放3306端口，并且设置所有主机都可以以root用户使用密码登录
//数据库工具类,使用单例模式进行设计
class CDBHelper
{
public:
    CDBHelper();
    ~CDBHelper();
    CDBHelper(CDBHelper& dbHelper);
    std::string multiMytesChange(std::string& sql); //将sql语句中含有的中文乱码情况解决 先转CP_UTF8 再转CP_ACP
//    static CDBHelper* getInstance();
    BOOL sqlExcute(const std::string& sql, const std::string& database = "mysql",const std::string& user="root",const std::string& password = "xfy030221.");//sql 执行语句，用于执行不带返回数据的sql语句 默认参数是必须往前赋值，有默认值的在后面
    int sqlQueryCount(const std::string& sql, const std::string& database = "mysql",const std::string& user="root",const std::string& password = "xfy030221."); //使用sql查询，并且返回的是查询结果的行数
    std::vector<std::vector<std::string>> sqlQuery(const std::string& sql, const std::string& database = "mysql", const std::string& user = "root", const std::string& password = "xfy030221.");//使用sql查询，并且返回查询结果
private:
    MYSQL* m_mysql = nullptr;
    void initMysql();
    BOOL ConnectDB(const std::string& database = "mysql", const std::string& user = "root", const std::string& password = "xfy030221.");
    void disConnectDB();
    void distoryMysql();
//    static CDBHelper* m_instance;
//    static void releaseInstance();

//    void operator=(CDBHelper& dbHelper);
//    class  CHelper {
//    public:
//        CHelper()
//        {
//            CDBHelper::getInstance();
//        }
//        ~CHelper()
//        {
//            CDBHelper::releaseInstance();
//        }
//    };
//    static CHelper m_helper;
};

#endif // DBHELPER_H
