/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbmanager.c
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
#include "dbmanager.h"
/**********************************************************************
* 函数名称：db_callback
* 功能描述：回调函数
* 访问的表：
* 修改的表：
* 输入参数：无
* 输出参数：无
* 返 回 值：  0          成功
             -1          失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}
/**********************************************************************
* 函数名称：db_conn_init
* 功能描述： sqlite数据库连接
* 访问的表：
* 修改的表：
* 输入参数：const char * dbname,数据库名称
* 输出参数：struct sqlite3 **client
* 返 回 值：  0          成功
-1          失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_conn_init(const char * dbname ,sqlite3 **client)
{
	if (NULL != dbname)
	{
        char *zErrMsg = 0;
		int  rc;
		rc = sqlite3_open(dbname, (sqlite3 **)client);
        //sqlite3_exec(*client, "vacuum;", callback, 0, &zErrMsg);
    	if ( rc ) {
			fprintf(stdout, "Can't open database %s\n", dbname);
			exit(0);
			return -1;
		}
		else {
			fprintf(stdout, "Opened database successfully\n");
			return 0;
		}
        sqlite3_free(zErrMsg);
	}
    printf("Parameter is NULL\n");
    return -1;
}
/**********************************************************************
* 函数名称：db_conn_close
* 功能描述： sqlite数据库断开连接
* 访问的表：
* 修改的表：
* 输入参数：sqlite3      *client,数据库名称
* 输出参数：无
* 返 回 值：  0          成功
             -1          失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_conn_close(sqlite3 * client)
{
	if (NULL != client)
	{

		sqlite3_close(client);
		//client = NULL;
		fprintf(stdout, "Close database successfully\n");
		return 0;
	}
	printf("Parameter is NULL\n");
	exit(0);
	return -1;
}
/**********************************************************************
* 函数名称：db_querysql
* 功能描述： 执行数据库查询操作，返回记录集
* 访问的表：
* 修改的表：
* 输入参数：const char * sql,执行的sql语句
            sqlite3 *client,库

* 输出参数：dbResult,查询的记录集
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_querysql(const char * sql, sqlite3 * client,char ***dbResult,int *nRow, int *nColumn)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == sql || NULL == client)
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
			/* Execute SQL statement */
			rc = sqlite3_get_table(client, sql, dbResult, nRow, nColumn, &zErrMsg);
			if (rc != SQLITE_OK) {
				fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
			}
         
		    sqlite3_free(zErrMsg);
			return rc; /*执行成功*/
		}
}

/**********************************************************************
* 函数名称：db_openTransaction
* 功能描述： 事务开启
* 访问的表：
* 修改的表：
* 输入参数：sqlite3 *client,库
* 输出参数：
* 返 回 值：  0           成功
              -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_openTransaction(sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == client)                /*是否传入sql和库名*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
		rc = sqlite3_exec(client, "begin", NULL, NULL, &zErrMsg);    /*开启事务*/
		if (rc != SQLITE_OK) {
			fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
		}
        else {
		    printf("Open transaction successfully  ");
        }
        sqlite3_free(zErrMsg);
		return rc;

	}
}
/**********************************************************************
* 函数名称：int db_closeTransaction
* 功能描述：事务关闭
* 访问的表：
* 修改的表：
* 输入参数：sqlite3 *client,库
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/

INT32 db_closeTransaction(sqlite3 * client) {
	char *zErrMsg = 0;
	int  rc;
	if (NULL == client)                /*是否传入sql和库名*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
		rc = sqlite3_exec(client, "commit", NULL, NULL, &zErrMsg);        /*提交事务*/
		if (rc != SQLITE_OK) {
			fprintf(stdout, "Can't commit transaction: %s\n", zErrMsg);
		//	sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*事务回滚*/
		}
        else {
            printf("Commit transaction successfully\n");     /*提交成功*/
        }    
       	sqlite3_free(zErrMsg);
		return rc;
	}
}
/**********************************************************************
* 函数名称：db_executesql
* 功能描述： 执行数据库增删改操作
* 访问的表：
* 修改的表：
* 输入参数：const char * sql,执行的sql语句
            sqlite3 *client,库
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_executesql(const char * sql, sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == sql || NULL == client)                /*是否传入sql和库名*/
	{   
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
			rc = sqlite3_exec(client, sql, NULL, NULL, &zErrMsg);       /*执行sql语句*/
			if (rc != SQLITE_OK) {
				    fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
					sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*事务回滚*/
			}		
            sqlite3_free(zErrMsg);
	    	return rc;               
		}
}


/**********************************************************************
* 函数名称： db_definitionsql
* 功能描述： 执行数据库DDL操作
* 访问的表：
* 修改的表：
* 输入参数：const char * sql,执行的sql语句
            sqlite3 *client,库
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明： 数据库管理员操作
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_definitionsql(const char * sql, sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == sql || NULL == client)                /*是否传入sql和库名*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
   else {
           /* Execute SQL statement */
			rc = sqlite3_exec(client, sql, callback, NULL, &zErrMsg);       /*执行sql语句*/
			if (rc != SQLITE_OK) {
				fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
				sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*事务回滚*/

			}  
            else{
			    printf("Operation done successfully\n");         /*执行成功*/
            } 
            sqlite3_free(zErrMsg);
			return rc;
        }       
}
/**********************************************************************
* 函数名称： db_freetable
* 功能描述： 执行数据库释放表结果操作
* 访问的表：
* 修改的表：
* 输入参数：char **result,查询的记录集
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_freetable(char **result)
{
	sqlite3_free_table(result);
//	printf("Free table successfully\n");
	return 0;
}
/**********************************************************************
* 函数名称： db_attach
* 功能描述： 执行数据库间关联操作
* 访问的表：
* 修改的表：
* 输入参数：sqlite3 *client,库
            const char * dbname,关联数据库
            char * abbdbname,关联数据库简称
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_attach(sqlite3 *client,const char * dbname, char * abbdbname)
{
	char *zErrMsg = 0;
	int  rc;
	char attachsql[MAX_COMMAND_LENGTH];
	sprintf(attachsql, "ATTACH DATABASE '%s' as '%s'\n", dbname, abbdbname);
//	printf(attachsql, "ATTACH DATABASE '%s' as '%s'\n", dbname, abbdbname);
	rc = sqlite3_exec(client, attachsql, NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
	}

    sqlite3_free(zErrMsg);
	return rc;
}
/**********************************************************************
* 函数名称： db_detach
* 功能描述： 执行数据库间分离操作
* 访问的表：
* 修改的表：
* 输入参数:sqlite3 *client,库
           char * abbdbname,关联数据库简称
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_detach(sqlite3 *client,char * abbdbname)
{
	char *zErrMsg = 0;
	int  rc;
	char detachsql[MAX_COMMAND_LENGTH];
	sprintf(detachsql, "DETACH DATABASE '%s'\n", abbdbname);
	rc = sqlite3_exec(client, detachsql, NULL, NULL, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
	}
	//printf("Detach database successfully\n");
    sqlite3_free(zErrMsg);
	return rc;
}

/**********************************************************************
* 函数名称： db_prepare
* 功能描述： 执行插入准备操作
* 访问的表：
* 修改的表：
* 输入参数： sqlite3 *client,库
             const char * sql,sql语句
* 输出参数：
* 返 回 值：  0           成功
             -1           失败
* 其它说明：必须用通配符
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_prepare(sqlite3 *client,const char * sql,sqlite3_stmt **stmt)
{
	if (sqlite3_prepare_v2(client, sql, -1, stmt, NULL) != SQLITE_OK) {
		printf("Sql prepare failed!");
		exit(0);
		return -1;
	}
	return 0;
}

/**********************************************************************
* 函数名称： db_bind_int
* 功能描述： 执行数值绑定操作
* 访问的表：
* 修改的表：
* 输入参数：int ncount, 字段顺序
            unsigned int value,数值
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/

void db_bind_int(sqlite3_stmt * stmt,int ncount, unsigned int value)
{
	sqlite3_bind_int64(stmt, ncount, value);
}

/**********************************************************************
* 函数名称： db_step
* 功能描述： 执行操作
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
INT32 db_step(sqlite3 *client,sqlite3_stmt * stmt)
{
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		sqlite3_reset(stmt);
		fprintf(stderr, "SQL error:%s\n", sqlite3_errmsg(client));
		return -1;
	}
	else {
		//重新初始化该sqlite3_stmt对象绑定的变量。
		sqlite3_reset(stmt);
		return 0;
     }
}
/**********************************************************************
* 函数名称： db_finalize
* 功能描述： 执行释放操作
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/
void db_finalize(sqlite3_stmt * stmt) {
	sqlite3_finalize(stmt);  //释放变量
}

/**********************************************************************
* 函数名称： db_create_function
* 功能描述： 执行注册函数
* 访问的表：
* 修改的表：
* 输入参数：
* 输出参数：
* 返 回 值：
* 其它说明：
* 修改日期     版本号     修改人         修改内容
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          创建
***********************************************************************/

void db_create_function(sqlite3 *client,const char *FunctionName,int nArg, int eTextRep, void *pApp, void *Function , void *xStep, void *xFinal)
{
	sqlite3_create_function(client, FunctionName, nArg, eTextRep, pApp, Function, xStep, xFinal);
}