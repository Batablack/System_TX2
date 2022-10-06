//
// Created by sgb on 5/18/22.
//
#include "main.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h" // s
#include "cfg.h"
#include "bcflag.h"
#include "signal.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <string.h>
#include <time.h>
#include <sys/time.h>



using std::cout;
using std::endl;
using std::string;
using json = nlohmann::json;
using namespace spdlog;
auto file_logger = spdlog::rotating_logger_mt(log_name, get_path(log_path),1024 * 1024 * 1, 1);

HttpCfg CFG;
// Handle interrupts, like Ctrl-C
static int s_signo;
static void signal_handler(int signo) {
    s_signo = signo;
}

int settime(const std::string stime)
{
    int itime = atoi(stime.c_str()) + 8*3600;
    time_t ntime =(time_t)itime;
    struct tm * ctime = gmtime(&ntime);
    cout << "time_now:" << asctime(ctime) << endl;
    file_logger->info("time_now: {}",asctime(ctime));
//    char datetime[256] = {};
//    sprintf(datetime,"date -s \"%d-%d-%d %02d:%02d:%02d\"",ctime->tm_year+1900,ctime->tm_mon+1,ctime->tm_mday,ctime->tm_hour,ctime->tm_min,ctime->tm_sec);
//    system(datetime);
//    system("hwclock -w");
    return 1;
}

/*
 * http中断函数
 * */
static void server_fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
    std::cout << "ev : " << ev << std::endl;
    file_logger->info("ev : {}",ev);
    if (ev == MG_EV_HTTP_MSG) {
        //hm在整个switch语句里生效，case后加一个{}，限定作用域
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        //在终端打印请求信息
        string method;
        method.assign(hm->method.ptr, hm->method.len);
        cout << "method: " << method << endl;
        file_logger->info("method: {}", method);
        string uri;
        uri.assign(hm->uri.ptr, hm->uri.len);
        cout << "uri: " << uri << endl;
        file_logger->info("uri: {}", uri);
        //匹配本次的请求是否为指定的uri请求
        if (mg_http_match_uri(hm, "/connectTest")) {
            //连接测试
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "------------connectTest-------------" << endl;
            file_logger->info("------------connectTest-------------");
            if (!body.empty()) {
                cout << "------------body:" << body << endl;
                file_logger->info("------------body: {}", body);
                settime(body);
            }
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

            //自己组织简单响应

        }
        if (mg_http_match_uri(hm, "/addChipUser")) {
            cout << "------------addChipUser-------------" << endl;
            file_logger->info("------------addChipUser-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            file_logger->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            file_logger->info("body: {}", body);
            cout << "*****************" << endl;
            FILE *bfp = NULL;
            bfp = fopen(get_path(keyvalue_path), "w");
            fputs(body.c_str(), bfp);
            fclose(bfp);

            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

            //自己组织简单响应
        }
        if (mg_http_match_uri(hm, "/endDetect")) {
            cout << "------------endDetect-------------" << endl;
            file_logger->info("------------endDetect-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            file_logger->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            file_logger->info("body: {}", body);
            cout << "*****************" << endl;
            FILE *tfp = NULL;
            tfp = fopen(get_path(svp_state_path), "w");
            fputs("0", tfp);
            fclose(tfp);
            set_flag(get_path(fnId_path),"-1");
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

            //自己组织简单响应
        }
        if (mg_http_match_uri(hm, "/modelFile")) {
            cout << "------------modelFile-------------" << endl;
            file_logger->info("------------modelFile-------------");
            //保存文件路径
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            file_logger->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            file_logger->info("body: {}", body);
            cout << "*****************" << endl;
            if (!body.empty()) {
                FILE *bfp = NULL;
                bfp = fopen(get_path(fileaddrs_path), "w");
                fputs(body.c_str(), bfp);
                fclose(bfp);
                set_flag(get_path(Http_server_flag_path), "1");
                set_flag(get_path(svp_state_path), "1");
            }

            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "get_body:%s", body.c_str());

        }
        if (mg_http_match_uri(hm, "/getCurrentFn")) {
            cout << "------------getCurrentFn-------------" << endl;
            file_logger->info("------------getCurrentFn-------------");
            //增加芯片用户，保存用户名密码
            string body, bmessage;
            bmessage.assign(hm->message.ptr, hm->message.len);
            body.assign(hm->body.ptr, hm->body.len);
            cout << "bmessage:  " << bmessage << endl;
            file_logger->info("bmessage: {}", bmessage);
            cout << "*****************" << endl;
            cout << "body:  " << body << endl;
            file_logger->info("body: {}", body);
            cout << "*****************" << endl;
            if (!ifexists(get_path(fnId_path))) file_logger->error("not find %s",get_path(fnId_path));
            int fnId = get_flag(get_path(fnId_path));
            file_logger->info("fnId: {}", fnId);
            mg_http_reply(c, 200,
                          "Access-Control-Allow-Origin: *\r\n"
                          "Access-Control-Allow-Methods: GET,POST,DELETE,PUT\r\n"
                          "Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With , yourHeaderFeild\r\n",
                          "%d",fnId);

            //自己组织简单响应
        }
    }
}


void init()
{
    set_flag(get_path(Http_server_flag_path),"0");
    loadcfg(get_path(system_cfg_path),CFG);
    showcfg(CFG,file_logger);
}


int main(int argc, char *argv[]) {
    // Initialise stuff
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    file_logger->set_level(spdlog::level::info);
    file_logger->flush_on(spdlog::level::trace);
    init();
    struct mg_mgr server_mgr;
    mg_mgr_init(&server_mgr);      // Init manager
    mg_http_listen(&server_mgr, CFG.URL, server_fn, &server_mgr);  // Setup listener
    cout<<"wait listen\r\n" <<endl;
    file_logger->info("wait listen");
    while (s_signo == 0) mg_mgr_poll(&server_mgr, 1000);
    mg_mgr_free(&server_mgr);
    MG_INFO(("Exiting on signal %d", s_signo));
    return 0;
}
