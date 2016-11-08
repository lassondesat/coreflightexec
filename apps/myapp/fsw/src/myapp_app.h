/*=======================================================================================
** File Name:  myapp_app.h
**
** Title:  Header File for MYAPP Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  To define MYAPP's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _MYAPP_APP_H_
#define _MYAPP_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "myapp_platform_cfg.h"
#include "myapp_mission_cfg.h"
#include "myapp_private_ids.h"
#include "myapp_private_types.h"
#include "myapp_perfids.h"
#include "myapp_msgids.h"
#include "myapp_msg.h"



/*
** Local Defines
*/
#define MYAPP_TIMEOUT_MSEC    1000

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[MYAPP_EVT_CNT];

    /* CFE scheduling pipe */
    CFE_SB_PipeId_t  SchPipeId; 
    uint16           usSchPipeDepth;
    char             cSchPipeName[OS_MAX_API_NAME];

    /* CFE command pipe */
    CFE_SB_PipeId_t  CmdPipeId;
    uint16           usCmdPipeDepth;
    char             cCmdPipeName[OS_MAX_API_NAME];
    
    /* CFE telemetry pipe */
    CFE_SB_PipeId_t  TlmPipeId;
    uint16           usTlmPipeDepth;
    char             cTlmPipeName[OS_MAX_API_NAME];

    /* Task-related */
    uint32  uiRunStatus;
    
    /* Input data - from I/O devices or subscribed from other apps' output data.
       Data structure should be defined in myapp/fsw/src/myapp_private_types.h */
    MYAPP_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in myapp/fsw/src/myapp_private_types.h */
    MYAPP_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in myapp/fsw/src/myapp_msg.h */
    MYAPP_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} MYAPP_AppData_t;

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/
int32  MYAPP_InitApp(void);
int32  MYAPP_InitEvent(void);
int32  MYAPP_InitData(void);
int32  MYAPP_InitPipe(void);

void  MYAPP_AppMain(void);

void  MYAPP_CleanupCallback(void);

int32  MYAPP_RcvMsg(int32 iBlocking);

void  MYAPP_ProcessNewData(void);
void  MYAPP_ProcessNewCmds(void);
void  MYAPP_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  MYAPP_ReportHousekeeping(void);
void  MYAPP_SendOutData(void);

boolean  MYAPP_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _MYAPP_APP_H_ */

/*=======================================================================================
** End of file myapp_app.h
**=====================================================================================*/
    