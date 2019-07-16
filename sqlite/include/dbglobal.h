/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbglobal.h
* 文件标识：
* 内容摘要： dbglobal.c的头文件
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
#ifndef _DBGLOBAL_H
#define _DBGLOBAL_H
#include "sqlite3.h" 
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <sys/select.h>
#include <asm/errno.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>

#ifndef INT32
#define INT32           int
#endif


/***********************************************************
* 变量声明*
***********************************************************/


#define  MAX_PATH_LENGTH  100              /*文件路径的最大长度*/

#define  MAX_FILENAME_LENGTH  50           /*文件名最大长度*/
#define  MAX_DATABASE_NUM  5               /*数据库个数*/
#define  MAX_COMMAND_LENGTH  1024          /*命令的最大长度*/
#define  BUF_SIZE 1024 


/*公共基本信息*/
typedef struct DBCommon_Info
{
	char BigQueue[MAX_PATH_LENGTH];
	char Log[MAX_PATH_LENGTH];              
	char Net[MAX_PATH_LENGTH];
}T_DBCommonInfo;

/*公共基本信息*/
typedef struct DBRemote_Info
{
	char remoteIP[MAX_FILENAME_LENGTH];
	char remoteUser[MAX_FILENAME_LENGTH];
	char remotePass[MAX_FILENAME_LENGTH];
	char localFilePath[MAX_PATH_LENGTH];
	char remoteFilePath[MAX_PATH_LENGTH];
  	char RCC_localFilePath[MAX_PATH_LENGTH];
	char RCC_remoteFilePath[MAX_PATH_LENGTH];
}T_DBRemoteInfo;


/*表基本信息*/
typedef struct Table_Info
{
	char **dbResult; /*字段值*/
	int nRow;       /*记录数*/
	int nColumn;    /*字段数*/
}T_TableInfo;



/*公共基本信息*/
 extern T_DBCommonInfo g_tDBCommonInfo; 
 extern T_TableInfo g_tTableInfo;
 extern T_DBRemoteInfo g_tRemoteInfo;
 //char db_buf[BUF_SIZE];
// extern sqlite3 *db;
 
/*************************************************************
* 函数原型 *
************************************************************/

/*从指定配置文件读取配置信息到内存(main.c使用)*/
 INT32 db_readCfg(char * filename);
/*初始化内存函数*/
INT32 db_inti_GlobalMemInfo(void);
/*初始化进程*/
INT32 db_init_Global(void);



/*SQLITE数据库连接*/
/*SQLITE *db_conn_init(库名);*/
INT32  db_conn_init(const char * dbname,sqlite3 **client);
/*SQLITE数据库断开连接*/
/*SQLITE *db_conn_close(库名);*/
INT32  db_conn_close(sqlite3 *client);
/*SQLITE *db_openTransaction(库名);*/
INT32 db_openTransaction(sqlite3 *client);
/*SQLITE *db_closeTransaction(库名);*/
INT32 db_closeTransaction(sqlite3 *client);
/*SQLITE数据库查询*/
/*SQLITE *db_querysql(sql语句,库名,数组,行数,列数);*/
INT32 db_querysql(const char * sql, sqlite3 *client, char ***dbResult, int *nRow, int *nColumn);
/*SQLITE数据库增删改*/
/*SQLITE *db_executesql(sql语句,库名);*/
INT32 db_executesql(const char * sql, sqlite3 *client);
/*SQLITE释放表结果操作*/
/*SQLITE *db_executesql(sql结果);*/
INT32 db_freetable(char **result);
/*SQLITE数据库DDL操作*/
/*SQLITE *db_definitionsql(sql语句,库名);*/
INT32 db_definitionsql(const char * sql, sqlite3 *client);
/*SQLITE数据库关联*/
/*SQLITE *db_attach(关联库名,关联库名简称);*/
INT32 db_attach(sqlite3 *client,const char * dbname, char * abbdbname);
/*SQLITE数据库分离*/
/*SQLITE *db_detach(关联库名简称);*/
INT32 db_detach(sqlite3 *client,char * abbdbname);
/*SQLITE创建数据库操作*/
/*SQLITE *db_createtable(void);*/
INT32 db_createtable(void);
INT32 db_createtable_arp(char *db_name);

/*SQLITE 插入准备*/
/*SQLITE *db_prepare(const char * sql,sqlite3_stmt ** stmt);*/
INT32 db_prepare(sqlite3 *client,const char * sql,sqlite3_stmt **stmt);
/*SQLITE 绑定值*/
/*SQLITE *db_bind_int(sqlite3_stmt * stmt,int ncount,int value);*/
void db_bind_int(sqlite3_stmt * stmt,int ncount, unsigned int value);
/*SQLITE 执行绑定值*/
/*SQLITE *db_step(sqlite3_stmt * stmt);*/
INT32 db_step(sqlite3 *client,sqlite3_stmt * stmt);
/*SQLITE 释放绑定值*/
/*SQLITE *db_finalize(sqlite3_stmt * stmt);*/
void db_finalize(sqlite3_stmt * stmt);
/*注册函数*/
void db_create_function(sqlite3 *client,const char *FunctionName, int nArg, int eTextRep, void *pApp, void *Function, void *xStep, void *xFinal);

/*数据库备份*/
/*SQLITE *backupDb(源数据库,目标数据库,休眠时间,备份页数);*/
INT32 db_hotBackup(const char *zFilename, const char *aFilename, int sleepTime, int pageCount);
/*SQLITE *backupDb(本地文件名);*/
INT32 db_coldBackup(char * localFilename,char *remoteFilePath,char *localFilePath);

#endif

