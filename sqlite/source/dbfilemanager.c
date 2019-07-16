/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbfilemanager.c
* 文件标识：
* 内容摘要： 主要包括sqlite数据库的连接、操作等操作
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
#include "dbfilemanager.h"
/**********************************************************************
* 函数名称：db_fileExists
* 功能描述： 判断指定的文件是否存在
* 访问的表：
* 修改的表：
* 输入参数：const char * filename,文件名
* 输出参数：
* 返 回 值： 0-存在,-1-不存在
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
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
* 函数名称：db_readCfg
* 功能描述： 从指定配置文件读取配置信息到内存
* 访问的表：
* 修改的表：
* 输入参数：const char * filename,文件名
* 输出参数：
* 返 回 值：   0           成功
               -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          创建
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
* 函数名称：db_fileCompress
* 功能描述： 压缩本地文件
* 访问的表：
* 修改的表：
* 输入参数：const char * sourceFilename 本地文件
            const char * compressFilename 压缩后的文件
* 输出参数：
* 返 回 值：   0           成功
              -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          创建
***********************************************************************/
INT32 db_fileCompress(const char * sourceFilename, const char * compressFilename,const char * remoteIP, char * remotePass, char * remoteUser, char * remoteFilePath)
{
		//localFilename= malloc(strlen(localFilename)+1);
	    //printf( "sshpass -p %s ssh %s@%s\n", remotePass, remoteUser, remoteIP);
	    char command[MAX_COMMAND_LENGTH];
		sprintf(command,"sshpass -p %s ssh %s@%s\n", remotePass, remoteUser, remoteIP);//连接ssh
		FILE* fp = popen(command, "w");
		if (fp == NULL)
		{
			printf("Files compress unsuccessfully!\n");
			return -1;
		}
		fprintf(fp, "cd %s\n", remoteFilePath);//打开远程目录
		fprintf(fp, "tar -zcvf %s %s \n", compressFilename, sourceFilename);//压缩文件
		fprintf(fp, "exit\n");//退出ssh
		pclose(fp);
		return 0;
		}

/**********************************************************************
* 函数名称：db_fileDecompress
* 功能描述： 解压文件
* 访问的表：
* 修改的表：
* 输入参数：char * compressFilename 压缩文件,
            char * remotePass  远程密码, 
			char * remoteUser 远程用户,
			char * remoteIP 远程IP, 
			char * remoteFilePath 远程路径
* 输出参数：
* 返 回 值：   0           成功
              -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          创建
***********************************************************************/
INT32 db_fileDecompress(char * localFilePath,char * compressFilename)
{
        char command[MAX_COMMAND_LENGTH];
		//删除本地压缩文件,ssh连接远程
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
* 函数名称：db_Trim
* 功能描述：删除字符串空格
* 访问的表：
* 修改的表：
* 输入参数：char *str 字符串
* 输出参数：char *str
* 返 回 值：  
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/15         V1.0               liuxy          创建
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
