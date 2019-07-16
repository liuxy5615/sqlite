/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbmanager.c
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
#include "dbmanager.h"
/**********************************************************************
* �������ƣ�db_callback
* �����������ص�����
* ���ʵı�
* �޸ĵı�
* �����������
* �����������
* �� �� ֵ��  0          �ɹ�
             -1          ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ�db_conn_init
* ���������� sqlite���ݿ�����
* ���ʵı�
* �޸ĵı�
* ���������const char * dbname,���ݿ�����
* ���������struct sqlite3 **client
* �� �� ֵ��  0          �ɹ�
-1          ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ�db_conn_close
* ���������� sqlite���ݿ�Ͽ�����
* ���ʵı�
* �޸ĵı�
* ���������sqlite3      *client,���ݿ�����
* �����������
* �� �� ֵ��  0          �ɹ�
             -1          ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ�db_querysql
* ���������� ִ�����ݿ��ѯ���������ؼ�¼��
* ���ʵı�
* �޸ĵı�
* ���������const char * sql,ִ�е�sql���
            sqlite3 *client,��

* ���������dbResult,��ѯ�ļ�¼��
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
			return rc; /*ִ�гɹ�*/
		}
}

/**********************************************************************
* �������ƣ�db_openTransaction
* ���������� ������
* ���ʵı�
* �޸ĵı�
* ���������sqlite3 *client,��
* ���������
* �� �� ֵ��  0           �ɹ�
              -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_openTransaction(sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == client)                /*�Ƿ���sql�Ϳ���*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
		rc = sqlite3_exec(client, "begin", NULL, NULL, &zErrMsg);    /*��������*/
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
* �������ƣ�int db_closeTransaction
* ��������������ر�
* ���ʵı�
* �޸ĵı�
* ���������sqlite3 *client,��
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/

INT32 db_closeTransaction(sqlite3 * client) {
	char *zErrMsg = 0;
	int  rc;
	if (NULL == client)                /*�Ƿ���sql�Ϳ���*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
		rc = sqlite3_exec(client, "commit", NULL, NULL, &zErrMsg);        /*�ύ����*/
		if (rc != SQLITE_OK) {
			fprintf(stdout, "Can't commit transaction: %s\n", zErrMsg);
		//	sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*����ع�*/
		}
        else {
            printf("Commit transaction successfully\n");     /*�ύ�ɹ�*/
        }    
       	sqlite3_free(zErrMsg);
		return rc;
	}
}
/**********************************************************************
* �������ƣ�db_executesql
* ���������� ִ�����ݿ���ɾ�Ĳ���
* ���ʵı�
* �޸ĵı�
* ���������const char * sql,ִ�е�sql���
            sqlite3 *client,��
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_executesql(const char * sql, sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == sql || NULL == client)                /*�Ƿ���sql�Ϳ���*/
	{   
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
	else {
			rc = sqlite3_exec(client, sql, NULL, NULL, &zErrMsg);       /*ִ��sql���*/
			if (rc != SQLITE_OK) {
				    fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
					sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*����ع�*/
			}		
            sqlite3_free(zErrMsg);
	    	return rc;               
		}
}


/**********************************************************************
* �������ƣ� db_definitionsql
* ���������� ִ�����ݿ�DDL����
* ���ʵı�
* �޸ĵı�
* ���������const char * sql,ִ�е�sql���
            sqlite3 *client,��
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵���� ���ݿ����Ա����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_definitionsql(const char * sql, sqlite3 * client)
{
	char *zErrMsg = 0;
	int  rc;
	if (NULL == sql || NULL == client)                /*�Ƿ���sql�Ϳ���*/
	{
		printf("Parameter is NULL\n");
		return -1;
		exit(0);
	}
   else {
           /* Execute SQL statement */
			rc = sqlite3_exec(client, sql, callback, NULL, &zErrMsg);       /*ִ��sql���*/
			if (rc != SQLITE_OK) {
				fprintf(stdout, "SQL error:%d %s\n",rc,zErrMsg);
				sqlite3_exec(client, "rollback", NULL, 0, &zErrMsg);          /*����ع�*/

			}  
            else{
			    printf("Operation done successfully\n");         /*ִ�гɹ�*/
            } 
            sqlite3_free(zErrMsg);
			return rc;
        }       
}
/**********************************************************************
* �������ƣ� db_freetable
* ���������� ִ�����ݿ��ͷű�������
* ���ʵı�
* �޸ĵı�
* ���������char **result,��ѯ�ļ�¼��
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_freetable(char **result)
{
	sqlite3_free_table(result);
//	printf("Free table successfully\n");
	return 0;
}
/**********************************************************************
* �������ƣ� db_attach
* ���������� ִ�����ݿ���������
* ���ʵı�
* �޸ĵı�
* ���������sqlite3 *client,��
            const char * dbname,�������ݿ�
            char * abbdbname,�������ݿ���
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ� db_detach
* ���������� ִ�����ݿ��������
* ���ʵı�
* �޸ĵı�
* �������:sqlite3 *client,��
           char * abbdbname,�������ݿ���
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ� db_prepare
* ���������� ִ�в���׼������
* ���ʵı�
* �޸ĵı�
* ��������� sqlite3 *client,��
             const char * sql,sql���
* ���������
* �� �� ֵ��  0           �ɹ�
             -1           ʧ��
* ����˵����������ͨ���
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
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
* �������ƣ� db_bind_int
* ���������� ִ����ֵ�󶨲���
* ���ʵı�
* �޸ĵı�
* ���������int ncount, �ֶ�˳��
            unsigned int value,��ֵ
* ���������
* �� �� ֵ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/

void db_bind_int(sqlite3_stmt * stmt,int ncount, unsigned int value)
{
	sqlite3_bind_int64(stmt, ncount, value);
}

/**********************************************************************
* �������ƣ� db_step
* ���������� ִ�в���
* ���ʵı�
* �޸ĵı�
* ���������
* ���������
* �� �� ֵ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
INT32 db_step(sqlite3 *client,sqlite3_stmt * stmt)
{
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		sqlite3_reset(stmt);
		fprintf(stderr, "SQL error:%s\n", sqlite3_errmsg(client));
		return -1;
	}
	else {
		//���³�ʼ����sqlite3_stmt����󶨵ı�����
		sqlite3_reset(stmt);
		return 0;
     }
}
/**********************************************************************
* �������ƣ� db_finalize
* ���������� ִ���ͷŲ���
* ���ʵı�
* �޸ĵı�
* ���������
* ���������
* �� �� ֵ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/
void db_finalize(sqlite3_stmt * stmt) {
	sqlite3_finalize(stmt);  //�ͷű���
}

/**********************************************************************
* �������ƣ� db_create_function
* ���������� ִ��ע�ắ��
* ���ʵı�
* �޸ĵı�
* ���������
* ���������
* �� �� ֵ��
* ����˵����
* �޸�����     �汾��     �޸���         �޸�����
* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
* 2018/05/10         V1.0               liuxy          ����
***********************************************************************/

void db_create_function(sqlite3 *client,const char *FunctionName,int nArg, int eTextRep, void *pApp, void *Function , void *xStep, void *xFinal)
{
	sqlite3_create_function(client, FunctionName, nArg, eTextRep, pApp, Function, xStep, xFinal);
}