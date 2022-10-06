//
// Created by Administrator on 2022/8/23.
//

#include "cfg.h"

static json loadjson(const char* path)
{
    json j;
    std::ifstream i(path);
    i >> j;
    return j;
}

bool loadcfg(const char* path,HttpCfg& cfg)
{
    cout << "loadcfg" << endl;
    json j,httpcfg;
    j = loadjson(path);
    httpcfg = j.at("HttpServer_cfg");
    cfg.URL =new char [128];
    string tmp;
    tmp = httpcfg.at("url");
    strcpy(cfg.URL,tmp.c_str());
    cout << "FTP CFG DONE"<<endl;
}
bool showcfg(const HttpCfg& cfg,std::shared_ptr<logger> file_logger)
{
    file_logger->info("url:{}",cfg.URL);
    return true;
}

char *get_path(const char * path)
{
    char * fpath = new char [128];
    strcpy(fpath,Bpath);
    strcat(fpath,path);
    return fpath;
}