/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbinifile.h
* 文件标识：
* 内容摘要： dbinifile.c的头文件
* 其它说明：
* 当前版本：
* 作 者：liuxy
* 完成日期：2018年5月10日
*
* 修改记录1：
* 修改日期：
* 版本 号：
* 修改 人：
* 修改内容：
* 修改记录2：…
**********************************************************************/

#ifndef _DBINIFILE_H_
#define _DBINIFILE_H_
#include "dbglobal.h"

/*读取文件*/
int dbread_profile_string(char *section, char *key, char *value, int size, const char *default_value, const char *file);
int dbread_profile_int(char *section, char *key, int default_value, const char *file);


#endif 
