/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbfilemanager.h
* 文件标识：
* 内容摘要： filemanager.c的头文件
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
#ifndef _DBFILEMANAGER_H
#define _DBFILEMANAGER_H
#include "dbglobal.h"


/*************************************************************
* 函数原型 *
************************************************************/


/*判断指定的文件是否存在*/
 INT32 db_fileExists(const char * filename);
 /*压缩文件*/
 INT32 db_fileCompress(const char * sourceFilename, const char * compressFilename, const char * remoteIP, char * remotePass, char * remoteUser, char * remoteFilePath);
 /*解压文件(跨服务器)*/
 INT32 db_fileDecompress(char * localFilePath, char * compressFilename);

/*删除字符串空格*/
const char *db_Trim(const char *str);
#endif