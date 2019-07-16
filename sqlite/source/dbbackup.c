/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbbackup.c
* 文件标识：
* 内容摘要： 主要包括sqlite数据库的连接、操作等操作
* 其它说明：
* 当前版本：
* 作 者：liuxy
* 完成日期：2018年6月5日
*
* 修改记录1：
* 修改日期：
* 版本 号：
* 修改 人：
* 修改内容：
* 修改记录2：…
**********************************************************************/
#include "dbbackup.h"
/**********************************************************************
* 函数名称： db_hotBackup
* 功能描述： 热备份
* 访问的表： 
* 修改的表：
* 输入参数：const char *zFilename 源数据库,
            const char *aFilename 目标数据库,
            int sleepTime 休眠时间(ms),
            int pageCount 备份页数
* 输出参数：
* 返 回 值： 0-成功,-1-失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/06/05         V1.0               liuxy          创建
***********************************************************************/
INT32 db_hotBackup(const char *zFilename, const char *aFilename,int sleepTime,int pageCount )
{
	int rc,rt;     
	sqlite3 *zFile;  
	sqlite3_backup *pBackup;  
	sqlite3 *aFile;           
	rc = sqlite3_open(aFilename, &aFile);/*打开源数据库*/
	rt = sqlite3_open(zFilename, &zFile);/*打开目标数据库*/
	if (rc == SQLITE_OK && rt == SQLITE_OK) {
		pBackup = sqlite3_backup_init(zFile,"main",aFile, "main");/*初始化*/
		if (pBackup) {
			printf("Initialization is successfully\n");
			do {
				rc = sqlite3_backup_step(pBackup, pageCount);
				if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED) {
					sqlite3_sleep(sleepTime);
				}
			} while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);
			printf("Hot backup successfully\n");
			(void)sqlite3_backup_finish(pBackup);/*释放资源*/
		}
		else {
			printf("Initialization is unsuccessfully\n");
			return -1;
		}
	}
	else {
		fprintf(stderr, "Can't open objective database: %s\n", sqlite3_errmsg(zFile));
		fprintf(stderr, "Can't open original database: %s\n", sqlite3_errmsg(aFile));
		return -1;
	}
	(void)sqlite3_close(zFile); /*关闭目标数据库*/
	(void)sqlite3_close(aFile); /*关闭源数据库*/
	return 0;
};


/**********************************************************************
* 函数名称： db_coldBackup
* 功能描述： 冷备份(跨服务器)
* 访问的表：
* 修改的表：
* 输入参数：const char * localFilename,文件名
* 输出参数：
* 返 回 值： 0-成功,-1-失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/06/05         V1.0               liuxy          创建
***********************************************************************/
INT32 db_coldBackup(char * localFilename,char *remoteFilePath,char *localFilePath)
{
	/*int i,servernum;
	servernum = atoi(g_tDBCommonInfo.ServerNum);*/
	char command[MAX_COMMAND_LENGTH];
	char fileCompress[MAX_FILENAME_LENGTH];
	sprintf(fileCompress, "%s", "filename.tar.gz");//压缩后的文件名
	
	db_fileCompress(localFilename, fileCompress, g_tRemoteInfo.remoteIP, g_tRemoteInfo.remotePass, g_tRemoteInfo.remoteUser,remoteFilePath); //压缩文件
		sprintf(command, "sshpass -p %s  sftp %s@%s\n", g_tRemoteInfo.remotePass, g_tRemoteInfo.remoteUser, g_tRemoteInfo.remoteIP);//sftp连接
		FILE* fp = popen(command, "w");
		if (fp == NULL)
		{
			return -1;
		}
		fprintf(fp, "get %s%s %s\n",remoteFilePath, fileCompress, localFilePath);//sftp复制文件
		fprintf(fp, "rm %s%s\n", remoteFilePath, fileCompress);
		fprintf(fp, "exit\n");//退出sftp
		pclose(fp);//释放变量
		db_fileDecompress(localFilePath,fileCompress);//解压文件

	
	return 0;
}


