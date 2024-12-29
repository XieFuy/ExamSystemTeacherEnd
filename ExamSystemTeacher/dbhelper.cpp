#include "dbhelper.h"

//CDBHelper* CDBHelper::m_instance = nullptr;
//CDBHelper::CHelper CDBHelper::m_helper;

//CDBHelper* CDBHelper::getInstance()
//{
//    if (CDBHelper::m_instance == nullptr)
//    {
//        CDBHelper::m_instance = new CDBHelper();
//        return CDBHelper::m_instance;
//    }
//    return CDBHelper::m_instance;
//}

//void CDBHelper::releaseInstance()
//{
//    if (CDBHelper::m_instance != nullptr)
//    {
//        delete CDBHelper::m_instance;
//        CDBHelper::m_instance = nullptr;
//    }
//}

CDBHelper::CDBHelper()
{
//    std::cout << "数据库工具类单例对象已生成" << std::endl;
    std::cout << "database instance create!" << std::endl;
}

CDBHelper::~CDBHelper()
{
//    std::cout << "数据库工具类单例对象已释放" << std::endl;
    std::cout << "dataBase instance release!" << std::endl;
}

CDBHelper::CDBHelper(CDBHelper& dbHelper){}

//void CDBHelper::operator=(CDBHelper& dbHelper){}

void CDBHelper::initMysql()
{
    if (this->m_mysql == nullptr)
    {
        this->m_mysql = new MYSQL();
        this->m_mysql =  mysql_init(this->m_mysql);
    }
}

BOOL CDBHelper::ConnectDB(const std::string& database , const std::string& user , const std::string& password )
{
    //设置字符编码
    mysql_options(this->m_mysql, MYSQL_SET_CHARSET_NAME, "GBK"); //如果想插入中文的话，在连接数据库之前要设置字符编码为GBK 。。。(nnd想了好久才解决)
    this->m_mysql =  mysql_real_connect(this->m_mysql,"120.78.122.212",user.c_str(),password.c_str(),database.c_str(),3306,nullptr,0);
    if (this->m_mysql == nullptr)
    {
        return FALSE;
    }
    return TRUE;
}

std::vector<std::vector<std::string>> CDBHelper::sqlQuery(const std::string& sql, const std::string& database, const std::string& user, const std::string& password)
{
    this->initMysql();
    this->ConnectDB(database,user,password);
    int ret = mysql_real_query(this->m_mysql, sql.c_str(), sql.size());
    if (ret != 0)
    {
        std::cout << "错误码：" << mysql_errno(this->m_mysql) << "错误提示：" << mysql_error(this->m_mysql) << std::endl;
        this->disConnectDB();
        this->distoryMysql();
        return std::vector<std::vector<std::string>>();
    }

    //获取查询结果
    MYSQL_RES* result =  mysql_store_result(this->m_mysql);
    std::vector<std::vector<std::string>> m_result; //返回的结果集
    if (result != nullptr)
    {
        unsigned int nFields =  mysql_num_fields(result);
        uint64_t nRows =  mysql_num_rows(result);
        MYSQL_FIELD* fields =  mysql_fetch_fields(result);
        for (uint64_t i = 0; i < nRows; i++)
        {
            MYSQL_ROW row =  mysql_fetch_row(result);
            std::vector<std::string> m_row;
            for (unsigned int j = 0 ; j < nFields;j++)  //如果返回值为null的话就插入一个'null'的字符串
            {
                std::cout<<row[j]<<std::endl;
                if(row[j] == nullptr)
                {
                    m_row.push_back("null");
                    continue;
                }
                m_row.push_back(row[j]);
            }
            m_result.push_back(m_row);
        }
    }
    this->disConnectDB();
    this->distoryMysql();
    return m_result;
}

BOOL CDBHelper::sqlExcute(const std::string& sql, const std::string& database, const std::string& user , const std::string& password )
{
    this->initMysql();
    this->ConnectDB(database,user,password);
   // 确保客户端设置了正确的字符集
    //mysql_set_character_set(this->m_mysql,"utf8");
    //std::u32string wSql = sql.c_str();
    int ret =  mysql_real_query(this->m_mysql,sql.c_str(),sql.size());
    if (ret != 0)
    {
        std::cout << "错误码：" << mysql_errno(this->m_mysql) << "错误提示：" << mysql_error(this->m_mysql) << std::endl;
        this->disConnectDB();
        this->distoryMysql();
        return FALSE;
    }
    this->disConnectDB();
    this->distoryMysql();
    return TRUE;
}

void CDBHelper::disConnectDB()
{
    mysql_close(this->m_mysql);
}

void CDBHelper::distoryMysql()
{
    if (this->m_mysql != nullptr)
    {
        delete this->m_mysql;
        this->m_mysql = nullptr;
    }
}

int CDBHelper::sqlQueryCount(const std::string& sql, const std::string& database ,const std::string& user,const std::string& password)
{
    this->initMysql();
    this->ConnectDB(database,user,password);
    int Count = -1;
    int ret =  mysql_real_query(this->m_mysql,sql.c_str(),sql.size());
    if (ret != 0)
    {
        return -1;
    }
    MYSQL_RES* result =  mysql_store_result(this->m_mysql);
    if (result != nullptr) //说明有返回结果集
    {
        unsigned int fields =  mysql_num_fields(result);
        uint64_t rows =  mysql_num_rows(result);
        MYSQL_FIELD* field = mysql_fetch_fields(result); //获取到所有的列
        for (uint64_t i = 0; i < rows;i++)
        {
            MYSQL_ROW row =  mysql_fetch_row(result);
            for (unsigned int j = 0; j < fields;j++)
            {
                Count = std::atoi(row[j]);
                //std::cout << "列属性：" << field[j].type << "列名：" << field[j].name << "值：" << row[j] << std::endl;
            }
        }
    }
    this->disConnectDB();
    this->distoryMysql();
    return Count;
}

std::string CDBHelper::multiMytesChange(std::string& sql)
{
    int size =  MultiByteToWideChar(CP_UTF8,0,sql.c_str(),-1,nullptr,0);
    std::wstring wStr(size,'\0');
    MultiByteToWideChar(CP_UTF8,0,sql.c_str(),-1,&wStr[0],size);
    //再转为正常的多字节
    size = WideCharToMultiByte(CP_ACP,0,&wStr[0],wStr.size(),nullptr,0,nullptr,nullptr);
    std::string ret(size,'\0');
    WideCharToMultiByte(CP_ACP,0,&wStr[0],wStr.size(),&ret[0],size,nullptr,nullptr);
    return ret;
}
