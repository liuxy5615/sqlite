/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbglobal.h
* �ļ���ʶ��
* ����ժҪ�� dbglobal.c��ͷ�ļ�
* ����˵����
* ��ǰ�汾��
* �� �ߣ�liuxy
* ������ڣ�2018��5��10��
*
* �޸ļ�¼1��
* �޸����ڣ�
* �汾 �ţ�
* �޸� �ˣ�
* �޸����ݣ�
* �޸ļ�¼2����
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
* ��������*
***********************************************************/


#define  MAX_PATH_LENGTH  100              /*�ļ�·������󳤶�*/

#define  MAX_FILENAME_LENGTH  50           /*�ļ�����󳤶�*/
#define  MAX_DATABASE_NUM  5               /*���ݿ����*/
#define  MAX_COMMAND_LENGTH  1024          /*�������󳤶�*/
#define  BUF_SIZE 1024 


/*����������Ϣ*/
typedef struct DBCommon_Info
{
	char BigQueue[MAX_PATH_LENGTH];
	char Log[MAX_PATH_LENGTH];              
	char Net[MAX_PATH_LENGTH];
}T_DBCommonInfo;

/*����������Ϣ*/
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


/*�������Ϣ*/
typedef struct Table_Info
{
	char **dbResult; /*�ֶ�ֵ*/
	int nRow;       /*��¼��*/
	int nColumn;    /*�ֶ���*/
}T_TableInfo;



/*����������Ϣ*/
 extern T_DBCommonInfo g_tDBCommonInfo; 
 extern T_TableInfo g_tTableInfo;
 extern T_DBRemoteInfo g_tRemoteInfo;
 //char db_buf[BUF_SIZE];
// extern sqlite3 *db;
 
/*************************************************************
* ����ԭ�� *
************************************************************/

/*��ָ�������ļ���ȡ������Ϣ���ڴ�(main.cʹ��)*/
 INT32 db_readCfg(char * filename);
/*��ʼ���ڴ溯��*/
INT32 db_inti_GlobalMemInfo(void);
/*��ʼ������*/
INT32 db_init_Global(void);



/*SQLITE���ݿ�����*/
/*SQLITE *db_conn_init(����);*/
INT32  db_conn_init(const char * dbname,sqlite3 **client);
/*SQLITE���ݿ�Ͽ�����*/
/*SQLITE *db_conn_close(����);*/
INT32  db_conn_close(sqlite3 *client);
/*SQLITE *db_openTransaction(����);*/
INT32 db_openTransaction(sqlite3 *client);
/*SQLITE *db_closeTransaction(����);*/
INT32 db_closeTransaction(sqlite3 *client);
/*SQLITE���ݿ��ѯ*/
/*SQLITE *db_querysql(sql���,����,����,����,����);*/
INT32 db_querysql(const char * sql, sqlite3 *client, char ***dbResult, int *nRow, int *nColumn);
/*SQLITE���ݿ���ɾ��*/
/*SQLITE *db_executesql(sql���,����);*/
INT32 db_executesql(const char * sql, sqlite3 *client);
/*SQLITE�ͷű�������*/
/*SQLITE *db_executesql(sql���);*/
INT32 db_freetable(char **result);
/*SQLITE���ݿ�DDL����*/
/*SQLITE *db_definitionsql(sql���,����);*/
INT32 db_definitionsql(const char * sql, sqlite3 *client);
/*SQLITE���ݿ����*/
/*SQLITE *db_attach(��������,�����������);*/
INT32 db_attach(sqlite3 *client,const char * dbname, char * abbdbname);
/*SQLITE���ݿ����*/
/*SQLITE *db_detach(�����������);*/
INT32 db_detach(sqlite3 *client,char * abbdbname);
/*SQLITE�������ݿ����*/
/*SQLITE *db_createtable(void);*/
INT32 db_createtable(void);
INT32 db_createtable_arp(char *db_name);

/*SQLITE ����׼��*/
/*SQLITE *db_prepare(const char * sql,sqlite3_stmt ** stmt);*/
INT32 db_prepare(sqlite3 *client,const char * sql,sqlite3_stmt **stmt);
/*SQLITE ��ֵ*/
/*SQLITE *db_bind_int(sqlite3_stmt * stmt,int ncount,int value);*/
void db_bind_int(sqlite3_stmt * stmt,int ncount, unsigned int value);
/*SQLITE ִ�а�ֵ*/
/*SQLITE *db_step(sqlite3_stmt * stmt);*/
INT32 db_step(sqlite3 *client,sqlite3_stmt * stmt);
/*SQLITE �ͷŰ�ֵ*/
/*SQLITE *db_finalize(sqlite3_stmt * stmt);*/
void db_finalize(sqlite3_stmt * stmt);
/*ע�ắ��*/
void db_create_function(sqlite3 *client,const char *FunctionName, int nArg, int eTextRep, void *pApp, void *Function, void *xStep, void *xFinal);

/*���ݿⱸ��*/
/*SQLITE *backupDb(Դ���ݿ�,Ŀ�����ݿ�,����ʱ��,����ҳ��);*/
INT32 db_hotBackup(const char *zFilename, const char *aFilename, int sleepTime, int pageCount);
/*SQLITE *backupDb(�����ļ���);*/
INT32 db_coldBackup(char * localFilename,char *remoteFilePath,char *localFilePath);

#endif

