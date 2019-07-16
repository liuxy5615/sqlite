/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbbackup.c
* �ļ���ʶ��
* ����ժҪ�� ��Ҫ����sqlite���ݿ�����ӡ������Ȳ���
* ����˵����
* ��ǰ�汾��
* �� �ߣ�liuxy
* ������ڣ�2018��6��5��
*
* �޸ļ�¼1��
* �޸����ڣ�
* �汾 �ţ�
* �޸� �ˣ�
* �޸����ݣ�
* �޸ļ�¼2����
**********************************************************************/
#include "dbbackup.h"
/**********************************************************************
* �������ƣ� db_hotBackup
* ���������� �ȱ���
* ���ʵı� 
* �޸ĵı�
* ���������const char *zFilename Դ���ݿ�,
            const char *aFilename Ŀ�����ݿ�,
            int sleepTime ����ʱ��(ms),
            int pageCount ����ҳ��
* ���������
* �� �� ֵ�� 0-�ɹ�,-1-ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/06/05         V1.0               liuxy          ����
***********************************************************************/
INT32 db_hotBackup(const char *zFilename, const char *aFilename,int sleepTime,int pageCount )
{
	int rc,rt;     
	sqlite3 *zFile;  
	sqlite3_backup *pBackup;  
	sqlite3 *aFile;           
	rc = sqlite3_open(aFilename, &aFile);/*��Դ���ݿ�*/
	rt = sqlite3_open(zFilename, &zFile);/*��Ŀ�����ݿ�*/
	if (rc == SQLITE_OK && rt == SQLITE_OK) {
		pBackup = sqlite3_backup_init(zFile,"main",aFile, "main");/*��ʼ��*/
		if (pBackup) {
			printf("Initialization is successfully\n");
			do {
				rc = sqlite3_backup_step(pBackup, pageCount);
				if (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED) {
					sqlite3_sleep(sleepTime);
				}
			} while (rc == SQLITE_OK || rc == SQLITE_BUSY || rc == SQLITE_LOCKED);
			printf("Hot backup successfully\n");
			(void)sqlite3_backup_finish(pBackup);/*�ͷ���Դ*/
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
	(void)sqlite3_close(zFile); /*�ر�Ŀ�����ݿ�*/
	(void)sqlite3_close(aFile); /*�ر�Դ���ݿ�*/
	return 0;
};


/**********************************************************************
* �������ƣ� db_coldBackup
* ���������� �䱸��(�������)
* ���ʵı�
* �޸ĵı�
* ���������const char * localFilename,�ļ���
* ���������
* �� �� ֵ�� 0-�ɹ�,-1-ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/06/05         V1.0               liuxy          ����
***********************************************************************/
INT32 db_coldBackup(char * localFilename,char *remoteFilePath,char *localFilePath)
{
	/*int i,servernum;
	servernum = atoi(g_tDBCommonInfo.ServerNum);*/
	char command[MAX_COMMAND_LENGTH];
	char fileCompress[MAX_FILENAME_LENGTH];
	sprintf(fileCompress, "%s", "filename.tar.gz");//ѹ������ļ���
	
	db_fileCompress(localFilename, fileCompress, g_tRemoteInfo.remoteIP, g_tRemoteInfo.remotePass, g_tRemoteInfo.remoteUser,remoteFilePath); //ѹ���ļ�
		sprintf(command, "sshpass -p %s  sftp %s@%s\n", g_tRemoteInfo.remotePass, g_tRemoteInfo.remoteUser, g_tRemoteInfo.remoteIP);//sftp����
		FILE* fp = popen(command, "w");
		if (fp == NULL)
		{
			return -1;
		}
		fprintf(fp, "get %s%s %s\n",remoteFilePath, fileCompress, localFilePath);//sftp�����ļ�
		fprintf(fp, "rm %s%s\n", remoteFilePath, fileCompress);
		fprintf(fp, "exit\n");//�˳�sftp
		pclose(fp);//�ͷű���
		db_fileDecompress(localFilePath,fileCompress);//��ѹ�ļ�

	
	return 0;
}


