/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbgolbal.c
* �ļ���ʶ��
* ����ժҪ�� 
* ����˵����
* ��ǰ�汾��
* �� �ߣ�liuxy
* ������ڣ�2018��05��15��
*
* �޸ļ�¼1��
* �޸����ڣ�
* �汾 �ţ�
* �޸� �ˣ�
* �޸����ݣ�
* �޸ļ�¼2����
**********************************************************************/
#include "dbglobal.h"

/***********************************************************
* ��������*
***********************************************************/

/*����������Ϣ*/
T_DBCommonInfo g_tDBCommonInfo;
T_TableInfo g_tTableInfo;
T_DBRemoteInfo g_tRemoteInfo;
//char db_buf[BUF_SIZE];
//sqlite3 *db;

/**********************************************************************
* �������ƣ�db_inti_GlobalMemInfo
* ������������ʼ���ڴ�
* ���ʵı�
* �޸ĵı�
* ���������
* �����������
* �� �� ֵ��  0          �ɹ�
             -1          ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/

int db_inti_GlobalMemInfo(void)
{
	/*����������Ϣ��ʼ��*/
	memset(&g_tDBCommonInfo, 0, sizeof(g_tDBCommonInfo));
	memset(&g_tTableInfo, 0, sizeof(g_tTableInfo));
	memset(&g_tRemoteInfo, 0, sizeof(g_tRemoteInfo));
	return 0;
};
/**********************************************************************
* �������ƣ�db_inti_Global
* ������������ʼ������
* ���ʵı�
* �޸ĵı�
* ���������
* �����������
* �� �� ֵ��  0          �ɹ�
             -1          ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/

INT32 db_init_Global(void)
{
	if (0 == db_inti_GlobalMemInfo())
	{
		if (0 == db_readCfg(Makefle_D))
		{
			if (0 == db_createtable())
			{
				if (db_coldBackup("BigQueue*",g_tRemoteInfo.remoteFilePath,g_tRemoteInfo.localFilePath) || db_coldBackup("*",g_tRemoteInfo.RCC_remoteFilePath,g_tRemoteInfo.RCC_localFilePath)== 0 )
				{
					printf(" DB initialization exit!\n");
					return 0;
				}

				else
				{
					printf("Init menmory unsuccessfully!\n");
					return -1;
				}
			}
			else
			{
				printf(" Read configure unsuccessfully!\n");
				return -1;
			}
		}
		else
		{
			printf("Create database unsuccessfully!\n");
			return -1;
		}
	}
	else
	{
		printf(" Backup unsuccessfully!\n");
		return -1;
	}
};



			