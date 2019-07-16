/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbfilemanager.h
* �ļ���ʶ��
* ����ժҪ�� filemanager.c��ͷ�ļ�
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
#ifndef _DBFILEMANAGER_H
#define _DBFILEMANAGER_H
#include "dbglobal.h"


/*************************************************************
* ����ԭ�� *
************************************************************/


/*�ж�ָ�����ļ��Ƿ����*/
 INT32 db_fileExists(const char * filename);
 /*ѹ���ļ�*/
 INT32 db_fileCompress(const char * sourceFilename, const char * compressFilename, const char * remoteIP, char * remotePass, char * remoteUser, char * remoteFilePath);
 /*��ѹ�ļ�(�������)*/
 INT32 db_fileDecompress(char * localFilePath, char * compressFilename);

/*ɾ���ַ����ո�*/
const char *db_Trim(const char *str);
#endif