//
// Created by Administrator on 2022/8/23.
//

#ifndef DOWNLOADWK_DEMO_CFG_H
#define DOWNLOADWK_DEMO_CFG_H

#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include "spdlog/spdlog.h"


using json = nlohmann::json;
using std::string;
using std::cout;
using std::endl;
using namespace spdlog;

static const char *Bpath = "/home/nvidia/System/";

static const char *log_name = "HttpServer";
static const char *log_path = "log/log";
static const char *svp_state_path = "json/svp_state";
static const char *fnId_path = "json/fnId";
static const char *fileaddrs_path = "json/fileaddrs.json";
static const char *Http_server_flag_path = "json/Http_server_flag";
static const char *system_cfg_path = "json/system_cfg.json";
static const char *keyvalue_path = "json/keyvalue.json";


struct HttpCfg
{
    char* URL;
};


bool loadcfg(const char* path,HttpCfg& cfg);
bool showcfg(const HttpCfg& cfg,std::shared_ptr<logger> file_logger);
char *get_path(const char * path);
#endif //DOWNLOADWK_DEMO_CFG_H
