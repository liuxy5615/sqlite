/*********************************************************************
* ��Ȩ���� (C)2018, �Ͼ��Ű��ڻ�����������޹�˾��
*
* �ļ����ƣ� dbinifile.h
* �ļ���ʶ��
* ����ժҪ�� dbinifile.c��ͷ�ļ�
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

#ifndef _DBINIFILE_H_
#define _DBINIFILE_H_
#include "dbglobal.h"

/*��ȡ�ļ�*/
int dbread_profile_string(char *section, char *key, char *value, int size, const char *default_value, const char *file);
int dbread_profile_int(char *section, char *key, int default_value, const char *file);


#endif 
