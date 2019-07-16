/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbfilemanager.c
* �ļ���ʶ��
* ����ժҪ�� ��Ҫ����sqlite���ݿ�����ӡ������Ȳ���
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
#include "dbfilemanager.h"
/**********************************************************************
* �������ƣ�db_fileExists
* ���������� �ж�ָ�����ļ��Ƿ����
* ���ʵı�
* �޸ĵı�
* ���������const char * filename,�ļ���
* ���������
* �� �� ֵ�� 0-����,-1-������
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_fileExists(const char * filename)
{
	if ( NULL == filename)
	{
		printf("Parameter is NULL\n");
		return -1;
	}
	FILE* pf;

	pf = fopen(filename, "r");
	if (NULL == pf)
	{
        printf("File is not exist\n");
        return -1;
		exit(0);
	}
  	fclose(pf);

	return 0;
}
/**********************************************************************
* �������ƣ�db_readCfg
* ���������� ��ָ�������ļ���ȡ������Ϣ���ڴ�
* ���ʵı�
* �޸ĵı�
* ���������const char * filename,�ļ���
* ���������
* �� �� ֵ��   0           �ɹ�
               -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          ����
***********************************************************************/
INT32 db_readCfg(char * filename)
{
	if (NULL == filename)
	{
		printf("Parameter is NULL\n");
		return -1;
	}

	//[DATABASE]
	    char section[MAX_PATH_LENGTH]={0,};
    	sprintf(section, "%s", "DATABASE");
		(void)dbread_profile_string(section, "DbName", g_tDBCommonInfo.BigQueue, sizeof(g_tDBCommonInfo.BigQueue), NULL, filename);
		(void)dbread_profile_string(section, "LogDb", g_tDBCommonInfo.Log,sizeof(g_tDBCommonInfo.Log), NULL, filename);
		(void)dbread_profile_string(section, "NetDb", g_tDBCommonInfo.Net, sizeof(g_tDBCommonInfo.Net), NULL, filename);

		sprintf(section, "%s", "BACKUP");
		(void)dbread_profile_string(section, "RemoteIP", g_tRemoteInfo.remoteIP, sizeof(g_tRemoteInfo.remoteIP), NULL, filename);
		(void)dbread_profile_string(section, "RemoteUser", g_tRemoteInfo.remoteUser,sizeof(g_tRemoteInfo.remoteUser), NULL, filename);
		(void)dbread_profile_string(section, "RemotePass", g_tRemoteInfo.remotePass, sizeof(g_tRemoteInfo.remotePass), NULL, filename);
		(void)dbread_profile_string(section, "LocalFilePath", g_tRemoteInfo.localFilePath, sizeof(g_tRemoteInfo.localFilePath), NULL, filename);
		(void)dbread_profile_string(section, "RemoteFilePath", g_tRemoteInfo.remoteFilePath, sizeof(g_tRemoteInfo.remoteFilePath), NULL, filename);
        
		sprintf(section, "%s", "RCC_BACKUP");
        (void)dbread_profile_string(section, "LocalFilePath", g_tRemoteInfo.RCC_localFilePath, sizeof(g_tRemoteInfo.RCC_localFilePath), NULL, filename);
		(void)dbread_profile_string(section, "RemoteFilePath", g_tRemoteInfo.RCC_remoteFilePath, sizeof(g_tRemoteInfo.RCC_remoteFilePath), NULL, filename);
        

	    return 0;
}

/**********************************************************************
* �������ƣ�db_fileCompress
* ���������� ѹ�������ļ�
* ���ʵı�
* �޸ĵı�
* ���������const char * sourceFilename �����ļ�
            const char * compressFilename ѹ������ļ�
* ���������
* �� �� ֵ��   0           �ɹ�
              -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          ����
***********************************************************************/
INT32 db_fileCompress(const char * sourceFilename, const char * compressFilename,const char * remoteIP, char * remotePass, char * remoteUser, char * remoteFilePath)
{
		//localFilename= malloc(strlen(localFilename)+1);
	    //printf( "sshpass -p %s ssh %s@%s\n", remotePass, remoteUser, remoteIP);
	    char command[MAX_COMMAND_LENGTH];
		sprintf(command,"sshpass -p %s ssh %s@%s\n", remotePass, remoteUser, remoteIP);//����ssh
		FILE* fp = popen(command, "w");
		if (fp == NULL)
		{
			printf("Files compress unsuccessfully!\n");
			return -1;
		}
		fprintf(fp, "cd %s\n", remoteFilePath);//��Զ��Ŀ¼
		fprintf(fp, "tar -zcvf %s %s \n", compressFilename, sourceFilename);//ѹ���ļ�
		fprintf(fp, "exit\n");//�˳�ssh
		pclose(fp);
		return 0;
		}

/**********************************************************************
* �������ƣ�db_fileDecompress
* ���������� ��ѹ�ļ�
* ���ʵı�
* �޸ĵı�
* ���������char * compressFilename ѹ���ļ�,
            char * remotePass  Զ������, 
			char * remoteUser Զ���û�,
			char * remoteIP Զ��IP, 
			char * remoteFilePath Զ��·��
* ���������
* �� �� ֵ��   0           �ɹ�
              -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          ����
***********************************************************************/
INT32 db_fileDecompress(char * localFilePath,char * compressFilename)
{
        char command[MAX_COMMAND_LENGTH];
		//ɾ������ѹ���ļ�,ssh����Զ��
		sprintf(command, "cd %s\n tar -zxvf %s\n  rm -f %s\n", localFilePath, compressFilename, compressFilename);
		FILE* fp = popen(command, "w");
		if (fp == NULL)
		{
			return -1;
		}
		pclose(fp);
		return 0;
}

/**********************************************************************
* �������ƣ�db_Trim
* ����������ɾ���ַ����ո�
* ���ʵı�
* �޸ĵı�
* ���������char *str �ַ���
* ���������char *str
* �� �� ֵ��  
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          ����
***********************************************************************/
const char *db_Trim(const char *str)
	{
		/* Skip leading whitespace */
		while (*str && *str <= ' ') {
			str++;
		}
		return str;
	}
	/*unsigned int uLen = strlen(str);

	if (0 == uLen)
	{
		return '\0';
	}

	char *strRet = (char *)malloc(uLen + 1);
	memset(strRet, 0, uLen + 1);

	unsigned int i = 0, j = 0;
	for (i = 0; i<uLen + 1; i++)
	{
		if (str[i] != ' ')
		{
			strRet[j++] = str[i];
		}
	}
	strRet[j] = '\0';

	return strRet;
}
*/
