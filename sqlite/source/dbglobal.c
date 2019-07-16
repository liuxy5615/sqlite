/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbgolbal.c
* 文件标识：
* 内容摘要： 
* 其它说明：
* 当前版本：
* 作 者：liuxy
* 完成日期：2018年05月15日
*
* 修改记录1：
* 修改日期：
* 版本 号：
* 修改 人：
* 修改内容：
* 修改记录2：…
**********************************************************************/
#include "dbglobal.h"

/***********************************************************
* 变量定义*
***********************************************************/

/*公共基本信息*/
T_DBCommonInfo g_tDBCommonInfo;
T_TableInfo g_tTableInfo;
T_DBRemoteInfo g_tRemoteInfo;
//char db_buf[BUF_SIZE];
//sqlite3 *db;

/**********************************************************************
* 函数名称：db_inti_GlobalMemInfo
* 功能描述：初始化内存
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：无
* 返 回 值：  0          成功
             -1          失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/

int db_inti_GlobalMemInfo(void)
{
	/*基本配置信息初始化*/
	memset(&g_tDBCommonInfo, 0, sizeof(g_tDBCommonInfo));
	memset(&g_tTableInfo, 0, sizeof(g_tTableInfo));
	memset(&g_tRemoteInfo, 0, sizeof(g_tRemoteInfo));
	return 0;
};
/**********************************************************************
* 函数名称：db_inti_Global
* 功能描述：初始化进程
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：无
* 返 回 值：  0          成功
             -1          失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
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



			