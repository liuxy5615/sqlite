/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbmanager.h
* 文件标识：
* 内容摘要： dbmanager.c的头文件
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
#ifndef _DBMANAGER_H
#define _DBMANAGER_H
#include "dbglobal.h"

/***********************************************************
* 变量定义 *
***********************************************************/

/*************************************************************
* 函数原型 *
************************************************************/
 /*回调函数*/
 INT32 callback(void *NotUsed, int argc, char **argv, char **azColName);
#endif