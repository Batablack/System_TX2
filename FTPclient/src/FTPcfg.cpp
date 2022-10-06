#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "FTPcfg.h"
#include "spdlog/spdlog.h"


using json = nlohmann::json;
using std::string;
using std::cout;
using std::endl;


static json loadjson(const char* path)
{
    json j;
    std::ifstream i(path);
    i >> j;
    return j;
}

bool loadcfg(const char* path,ftp_cfg_para& ftpCfgPara)
{
    cout << "loadcfg" << endl;
    json j,ftpcfg;
    j = loadjson(path);
    ftpcfg = j.at("ftp_cfg");
    //为参数赋值：
    ftpCfgPara.HOST = new char[128];
    ftpCfgPara.USER = new char[128];
    ftpCfgPara.PWD = new char[128];
    string tmp;
    tmp = ftpcfg.at("host");
    strcpy(ftpCfgPara.HOST,tmp.c_str());
    tmp = ftpcfg.at("user");
    strcpy(ftpCfgPara.USER,tmp.c_str());
    tmp = ftpcfg.at("pwd");
    strcpy(ftpCfgPara.PWD,tmp.c_str());

    ftpCfgPara.PORT = ftpcfg.at("port");
    ftpCfgPara.MODEL_path = ftpcfg.at("MODEL_path");
    ftpCfgPara.PROGRAM_path = ftpcfg.at("PROGRAM_path");
    ftpCfgPara.CONFIG_path = ftpcfg.at("CONFIG_path");
    ftpCfgPara.PARAM_path = ftpcfg.at("PARAM_path");
    ftpCfgPara.LIB_path = ftpcfg.at("LIB_path");
    ftpCfgPara.START_path = ftpcfg.at("START_path");
    cout << "FTP CFG DONE"<<endl;
}

bool showcfg(const ftp_cfg_para& ftpCfgPara,std::shared_ptr<logger> file_logger)
{
    file_logger->info("host:{}",ftpCfgPara.HOST);
    file_logger->info("PORT:{}",ftpCfgPara.PORT);
    file_logger->info("user:{}",ftpCfgPara.USER);
    file_logger->info("pwd:{}",ftpCfgPara.PWD);
    file_logger->info("MODEL_path:{}",ftpCfgPara.MODEL_path);
    file_logger->info("PROGRAM_path:{}",ftpCfgPara.PROGRAM_path);
    file_logger->info("CONFIG_path:{}",ftpCfgPara.CONFIG_path);
    file_logger->info("PARAM_path:{}",ftpCfgPara.PARAM_path);
    file_logger->info("LIB_path:{}",ftpCfgPara.LIB_path);
    file_logger->info("START_path:{}",ftpCfgPara.START_path);
    return true;
}

char *get_path(const char * path)
{
    char * fpath = new char [128];
    strcpy(fpath,Bpath);
    strcat(fpath,path);
    return fpath;
}

//int main(void)
//{
//   loadcfg("/home/sgb/tmp/system_cfg.json");
//}
