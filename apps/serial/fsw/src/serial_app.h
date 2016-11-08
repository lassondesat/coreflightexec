/*=======================================================================================
** File Name:  serial_app.h
**
** Title:  Header File for SERIAL Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  To define SERIAL's internal macros, data types, global variables and
**           function prototypes
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _SERIAL_APP_H_
#define _SERIAL_APP_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "serial_platform_cfg.h"
#include "serial_mission_cfg.h"
#include "serial_private_ids.h"
#include "serial_private_types.h"
#include "serial_perfids.h"
#include "serial_msgids.h"
#include "serial_msg.h"



/*
** Local Defines
*/
#define SERIAL_TIMEOUT_MSEC    1000

/*
** Local Structure Declarations
*/
typedef struct
{
    /* CFE Event table */
    CFE_EVS_BinFilter_t  EventTbl[SERIAL_EVT_CNT];

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
       Data structure should be defined in serial/fsw/src/serial_private_types.h */
    SERIAL_InData_t   InData;

    /* Output data - to be published at the end of a Wakeup cycle.
       Data structure should be defined in serial/fsw/src/serial_private_types.h */
    SERIAL_OutData_t  OutData;

    /* Housekeeping telemetry - for downlink only.
       Data structure should be defined in serial/fsw/src/serial_msg.h */
    SERIAL_HkTlm_t  HkTlm;

    /* TODO:  Add declarations for additional private data here */
} SERIAL_AppData_t;

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
int32  SERIAL_InitApp(void);
int32  SERIAL_InitEvent(void);
int32  SERIAL_InitData(void);
int32  SERIAL_InitPipe(void);

void  SERIAL_AppMain(void);

void  SERIAL_CleanupCallback(void);

int32  SERIAL_RcvMsg(int32 iBlocking);

void  SERIAL_ProcessNewData(void);
void  SERIAL_ProcessNewCmds(void);
void  SERIAL_ProcessNewAppCmds(CFE_SB_Msg_t*);

void  SERIAL_ReportHousekeeping(void);
void  SERIAL_SendOutData(void);

boolean  SERIAL_VerifyCmdLength(CFE_SB_Msg_t*, uint16);

#endif /* _SERIAL_APP_H_ */

/*=======================================================================================
** End of file serial_app.h
**=====================================================================================*/
    