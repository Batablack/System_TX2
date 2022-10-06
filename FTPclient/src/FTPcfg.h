//
// Created by Administrator on 2022/8/23.
//

#ifndef DEMO_DEMO_H
#define DEMO_DEMO_H
#include <string>
#include "spdlog/spdlog.h"
using std::string;
using namespace spdlog;
struct ftp_cfg_para
{
    char* HOST;
    int PORT;
    char* USER;
    char* PWD;
    string MODEL_path;
    string PROGRAM_path;
    string CONFIG_path;
    string PARAM_path;
    string LIB_path;
    string START_path;
};

static const char *Bpath = "/home/nvidia/System/";

static const char *log_name = "FTP";
static const char *log_path = "log/log";
static const char *system_cfg_path = "json/system_cfg.json";
static const char *fileaddrs_path = "json/fileaddrs.json";
static const char *Http_server_flag_path = "json/Http_server_flag";
static const char *fnId_path = "json/fnId";



char *get_path(const char * path);

bool loadcfg(const char* path,ftp_cfg_para& ftpCfgPara);
bool showcfg(const ftp_cfg_para& ftpCfgPara,std::shared_ptr<logger> file_logger);
#endif //DEMO_DEMO_H
