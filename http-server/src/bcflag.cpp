//
// Created by Administrator on 2022/8/16.
//

#include "bcflag.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
using json = nlohmann::json;


/*
 * set_flag函数：设置标志文件某一标志
 * 输入：file_path 文件路径
 *      flag_name 标志名称
 *      flag  设置标志位
 * */
int set_flag(const char* file_path,const char* flag)
{
    FILE *tfp = NULL;
    tfp = fopen(file_path, "w");
    fputs(flag, tfp);
    fclose(tfp);
}

/*
 * get_flag：获取标志文件某一标志位值
 * 输入：file_path 文件路径
 *      flag_name 标志名称
 * 返回值：标志位值
 * */
int get_flag(const char* file_path)
{
    //判断是否有目标
    int svp_flag=0;
    FILE *fp = NULL;
    char buff[255];
    fp = fopen(file_path, "r");
    fgets(buff, 255, (FILE*)fp);
    svp_flag = atoi(buff);
    fclose(fp);
    return svp_flag;
}

