/*********************************************************************
* 版权所有 (C)2018, 南京信安融慧软件技术有限公司。
*
* 文件名称： dbinifile.c
* 文件标识：
* 内容摘要： ini文件的读写
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
#include "dbinifile.h"


#define MAX_FILE_SIZE 1024*16
#define LEFT_BRACE '['
#define RIGHT_BRACE ']'

static int load_ini_file(const char *file, char *buf, int *file_size)
{

	FILE *in = NULL;
	int i = 0;
	*file_size = 0;

	if (file == NULL || buf == NULL)
	{
		return 0;
	}

	in = fopen(file, "r");
	if (NULL == in)
	{
		return 0;
	}

	buf[i] = fgetc(in);

	/*load initialization file*/
	while (buf[i] != (char)EOF)
	{
		i++;
		/*file too big, you can redefine MAX_FILE_SIZE to fit the big file */
		if (i >= MAX_FILE_SIZE)
		{
			fclose(in);
			return 0;
		}
		buf[i] = fgetc(in);
	}

	buf[i] = '\0';
	*file_size = i;

	fclose(in);
	return 1;
}

static int newline(char c)
{
	return ('\n' == c || '\r' == c) ? 1 : 0;
}
static int end_of_string(char c)
{
	return '\0' == c ? 1 : 0;
}
static int left_barce(char c)
{
	return LEFT_BRACE == c ? 1 : 0;
}
static int isright_brace(char c)
{
	return RIGHT_BRACE == c ? 1 : 0;
}
static int parse_file(const char *section, const char *key, const char *buf, int *sec_s, int *sec_e,
	int *key_s, int *key_e, int *value_s, int *value_e)
{
	const char *p = buf;
	int i = 0;

	if (buf == NULL || (section == NULL || (strlen(section) == 0)) || (key == NULL || strlen(key) == 0))
	{
		return  1;
	}

	*sec_e = *sec_s = *key_e = *key_s = *value_s = *value_e = -1;

	while (!end_of_string(p[i]))
	{
		/*find the section*/
		if ((0 == i || newline(p[i - 1])) && left_barce(p[i]))
		{
			int section_start = i + 1;

			/*find the ']'*/
			do
			{
				i++;
			} while (!isright_brace(p[i]) && !end_of_string(p[i]));

			if (0 == strncmp(p + section_start, section, i - section_start)) {
				int newline_start = 0;

				i++;

				/*Skip over space char after ']'*/
				while (isspace(p[i]))
				{
					i++;
				}

				/*find the section*/
				*sec_s = section_start;
				*sec_e = i;

				while (!(newline(p[i - 1]) && left_barce(p[i])) && !end_of_string(p[i]))
				{
					int j = 0;
					/*get a new line*/
					newline_start = i;

					while (!newline(p[i]) && !end_of_string(p[i]))
					{
						i++;
					}

					/*now i  is equal to end of the line*/
					j = newline_start;

					if (';' != p[j]) /*skip over comment*/
					{
						while (j < i && p[j] != '=')
						{
							j++;
							if ('=' == p[j])
							{
								
								/*get number of space char before '='*/
								int number_blank = 0;
								while (isspace(p[j - number_blank - 1]) && (newline_start<j - number_blank))
								{
									number_blank++;
								}
								//if(strncmp(key,p+newline_start,j-newline_start)==0)
								

								if (strncmp(key, p + newline_start, j - newline_start - number_blank) == 0)
								{
									/*find the key ok*/
									*key_s = newline_start;
									*key_e = j - 1;

									
									/*Skip over space char after '='*/
									while (j < i && isspace(p[j + 1]))
									{
										j++;
									}
									
									*value_s = j + 1;
									*value_e = i;

									return 1;
								}
							}
						}
					}

					i++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}

/**
*@brief read string in initialization file\n
* retrieves a string from the specified section in an initialization file
*@param section [in] name of the section containing the key name
*@param key [in] name of the key pairs to value
*@param value [in] pointer to the buffer that receives the retrieved string
*@param size [in] size of result's buffer
*@param default_value [in] default value of result
*@param file [in] path of the initialization file
*@return 1 : read success; \n 0 : read fail
*/
int dbread_profile_string(char *section, char *key, char *value, int size, const char *default_value, const char *file)
{
	char buf[MAX_FILE_SIZE] = { 0 };
	int file_size;
	int sec_s, sec_e, key_s, key_e, value_s, value_e;

	/*check parameters*/

	if (section == NULL || (strlen(section) == 0))
	{
		return 0;
	}
	if (key == NULL || (strlen(key) == 0))
	{
		return 0;
	}
	if (value == NULL)
	{
		return 0;
	}
	if (size <= 0)
	{
		return 0;
	}
	if (file == NULL)
	{
		return 0;
	}


	if (!load_ini_file(file, buf, &file_size))
	{
		if (default_value != NULL)
		{
			strncpy(value, default_value, size);
		}
		return 0;
	}

	if (!parse_file(section, key, buf, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e))
	{
		if (default_value != NULL)
		{
			strncpy(value, default_value, size);
		}
		return 0; /*not find the key*/
	}
	else
	{
		int cpcount = value_e - value_s;

		if (size - 1 < cpcount)
		{
			cpcount = size - 1;
		}

		memset(value, 0, size);
		memcpy(value, buf + value_s, cpcount);
		value[cpcount] = '\0';

		return 1;
	}

}

/**
*@brief read int value in initialization file\n
* retrieves int value from the specified section in an initialization file
*@param section [in] name of the section containing the key name
*@param key [in] name of the key pairs to value
*@param default_value [in] default value of result
*@param file [in] path of the initialization file
*@return profile int value,if read fail, return default value
*/
int dbread_profile_int(char *section, char *key, int default_value,
	const char *file)
{
	char value[32] = { 0 };
	if (!dbread_profile_string(section, key, value, sizeof(value), NULL, file))
	{
		return default_value;
	}
	else
	{
		return atoi(value);
	}
}
