#include "dbglobal.h"


int main(int argc, char* argv[])
{    
    
     sqlite3 *conection;
     char insertSQL1[1000];
     char command[MAX_COMMAND_LENGTH];
     char **dbResult; int nRow; int nColumn;
     
  /*   sprintf(insertSQL1,"select a.SERV_NO,a.ITEM_ID,a.FUNC_FLAG,a.TUPLE_FLAG,a.PROT_NO,a.SIP0,a.DIP0,a.SPORT,a.DPORT,a.ACTIVETAG,a.GROUP_NO,a.TRUSTFLAG from RCP_V4V6_QUINARY_INFO a "
     "left join (select FUNC_FLAG,TUPLE_FLAG,PROT_NO,SIP0,DIP0,SPORT,DPORT,ACTIVETAG,GROUP_NO,TRUSTFLAG from RCP_V4V6_QUINARY_INFO where SIGN=0 and ACTIVETAG=0 and ((SOURCEHEAD=1 and GROUP_TYPE=0 and SERNO_CLI<>-1) or SOURCEHEAD=0)"
     "group by FUNC_FLAG,TUPLE_FLAG,PROT_NO,SIP0,DIP0,SPORT,DPORT ) b "
     "on a.FUNC_FLAG=b.FUNC_FLAG and a.TUPLE_FLAG=b.TUPLE_FLAG and a.PROT_NO=b.PROT_NO and a.SIP0=b.SIP0 and a.DIP0=b.DIP0 and a.SPORT=b.SPORT and a.DPORT=b.DPORT and b.FUNC_FLAG is not null "// and a.ACTIVETAG=0 "
     "where a.SIGN=0 and ((a.SOURCEHEAD=1 and a.GROUP_TYPE=0 and a.SERNO_CLI<>-1) or a.SOURCEHEAD=0)");
*/

     printf("Makefle_D = %s\n", Makefle_D);
	/*读取文件的内容*/
	if (0 == db_inti_GlobalMemInfo())
	{
	if (0 == db_readCfg(Makefle_D))
	{
	//	printf("%s\n", g_tDBCommonInfo.BigQueue);
        
 
         sprintf(command, "rm -f %sBigQueue.*",g_tRemoteInfo.localFilePath);    
    // 	 printf(command, "rm -f %sBigQueue.*\n",g_tRemoteInfo.localFilePath);   

	     system(command);
         
      
		if (0 == db_createtable())
		{

			db_conn_init(g_tDBCommonInfo.BigQueue,&conection);
            db_attach(conection,g_tDBCommonInfo.Log, "log");
            db_openTransaction(conection);

         // db_executesql(insertSQL1,conection);
         //   db_querysql(insertSQL1,conection, &dbResult, &nRow, &nColumn);
           db_closeTransaction(conection);
         //  db_freetable(dbResult);
           db_detach(conection, "log");
		   db_conn_close(conection);

        //   db_createtable_arp("arp");
       //db_coldBackup("BigQueue*",g_tRemoteInfo.remoteFilePath,g_tRemoteInfo.localFilePath);
       //db_coldBackup("*",g_tRemoteInfo.RCC_remoteFilePath,g_tRemoteInfo.RCC_localFilePath);
	    }
	 }
  }
}
