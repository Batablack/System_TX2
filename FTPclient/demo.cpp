//
// Created by Administrator on 2022/7/26.
//
#include "json.hpp"
#include <iostream>
#include <fstream>
#include "rjson.h"
#include "THFTPAPI.h"
#include <string>
#include "bcflag.h"
#include <unistd.h>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging
#include "FTPcfg.h"

using std::string;
using namespace nlohmann;
using namespace spdlog;
ftp_cfg_para ftp_cfg;

auto file_logger = rotating_logger_mt(log_name, get_path(log_path),1024 * 1024 * 1, 1);


string get_json_save_path(const char *ftype,const char *fname)
{
    string path;
    if (strcmp(ftype,"MODEL") == 0)
    {
        path = ftp_cfg.MODEL_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"PROGRAM") == 0)
    {
        path = ftp_cfg.PROGRAM_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"CONFIG") == 0)
    {
        path = ftp_cfg.CONFIG_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"PARAM") == 0)
    {
        path = ftp_cfg.PARAM_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"LIB") == 0)
    {
        path = ftp_cfg.LIB_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"START") == 0)
    {
        path = ftp_cfg.START_path;
        path = path + fname;
        return path;
    }
    if (strcmp(ftype,"ZIP") == 0)
    {
        path = ftp_cfg.START_path;
        path = path + fname;
        return path;
    }

}



static bool initftp()
{

    loadcfg(get_path(system_cfg_path),ftp_cfg);
    showcfg(ftp_cfg,file_logger);
    return true;
}

int main()
{
    char* fpath[8];  //目标文件
    char* ftype[8];
    char* fname[8];
    char* json_path = get_path(fileaddrs_path);
    char* json_save_path = new char[128];
    unsigned long long int filesize=0;
    file_logger->set_level(spdlog::level::info);
    file_logger->flush_on(spdlog::level::trace);
    initftp();

    while(1)
    {
        int get_path_flag = get_flag(get_path(Http_server_flag_path));
        file_logger->debug("获取到 flag 值");
        if (get_path_flag == -1) continue;
        else if(get_path_flag == 1)
        {
            std::cout<< "获取到新路径" << std::endl;
            file_logger->debug("获取到新路径");
            unsigned long num = js_getfilepath(fpath,ftype,fname,json_path);
            int fnId = js_getfnId(json_path);
            set_flag(get_path(fnId_path),fnId);
            file_logger->info("get fnId:{}", get_flag(get_path(fnId_path)));
            int socket = ftp_connect(ftp_cfg.HOST,ftp_cfg.PORT,ftp_cfg.USER,ftp_cfg.PWD);
            std::cout<< "-----------ftp_connected------------" << std::endl;
            file_logger->debug("-----------ftp_connected------------");
            for(int i = 0;i < num;i++ )
            {
                //s:目标文件位置
                //d:本地文件位置
                string savepath = get_json_save_path(ftype[i],fname[i]);
                std::cout<< "dest path: " << savepath << std::endl;
                file_logger->info("dest path: {}",savepath);
                strcpy(json_save_path,savepath.c_str());
                if (ftp_retrfile(socket, fpath[i], json_save_path ,&filesize, NULL)< -1)
                {
                    std::cout<< "read ftp file error,ftp path: " << fpath[i] << std::endl;
                    file_logger->info("read ftp file error,ftp path: {}",fpath[i]);
                    break;
                }
            }
            set_flag(get_path(Http_server_flag_path),"0");
            std::cout<< "success read size:" << filesize << std::endl;
            file_logger->info("success read size: {}",filesize);
            std::cout<< "start reboot ...." << std::endl;
            file_logger->info("start reboot ....");
        }
        sleep(2);
    }

    return 1;
}
