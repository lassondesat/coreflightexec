/*=======================================================================================
** File Name:  myapp_app.c
**
** Title:  Function Definitions for MYAPP Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  This source file contains all necessary function definitions to run MYAPP
**           application.
**
** Functions Defined:
**    Function X - Brief purpose of function X
**    Function Y - Brief purpose of function Y
**    Function Z - Brief purpose of function Z
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to all functions in the file.
**    2. List the external source(s) and event(s) that can cause the funcs in this
**       file to execute.
**    3. List known limitations that apply to the funcs in this file.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/

/*
** Pragmas
*/

/*
** Include Files
*/
#include <string.h>

#include "cfe.h"

#include "myapp_platform_cfg.h"
#include "myapp_mission_cfg.h"
#include "myapp_app.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

/*
** External Global Variables
*/

/*
** Global Variables
*/
MYAPP_AppData_t  g_MYAPP_AppData;

/*
** Local Variables
*/

/*
** Local Function Definitions
*/
    
/*=====================================================================================
** Name: MYAPP_InitEvent
**
** Purpose: To initialize and register event table for MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_EVS_Register
**    CFE_ES_WriteToSysLog
**
** Called By:
**    MYAPP_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_MYAPP_AppData.EventTbl
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 MYAPP_InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Create the event table */
    memset((void*)g_MYAPP_AppData.EventTbl, 0x00, sizeof(g_MYAPP_AppData.EventTbl));

    g_MYAPP_AppData.EventTbl[0].EventID = MYAPP_RESERVED_EID;
    g_MYAPP_AppData.EventTbl[1].EventID = MYAPP_INF_EID;
    g_MYAPP_AppData.EventTbl[2].EventID = MYAPP_INIT_INF_EID;
    g_MYAPP_AppData.EventTbl[3].EventID = MYAPP_ILOAD_INF_EID;
    g_MYAPP_AppData.EventTbl[4].EventID = MYAPP_CDS_INF_EID;
    g_MYAPP_AppData.EventTbl[5].EventID = MYAPP_CMD_INF_EID;

    g_MYAPP_AppData.EventTbl[ 6].EventID = MYAPP_ERR_EID;
    g_MYAPP_AppData.EventTbl[ 7].EventID = MYAPP_INIT_ERR_EID;
    g_MYAPP_AppData.EventTbl[ 8].EventID = MYAPP_ILOAD_ERR_EID;
    g_MYAPP_AppData.EventTbl[ 9].EventID = MYAPP_CDS_ERR_EID;
    g_MYAPP_AppData.EventTbl[10].EventID = MYAPP_CMD_ERR_EID;
    g_MYAPP_AppData.EventTbl[11].EventID = MYAPP_PIPE_ERR_EID;
    g_MYAPP_AppData.EventTbl[12].EventID = MYAPP_MSGID_ERR_EID;
    g_MYAPP_AppData.EventTbl[13].EventID = MYAPP_MSGLEN_ERR_EID;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(g_MYAPP_AppData.EventTbl,
                               MYAPP_EVT_CNT, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("MYAPP - Failed to register with EVS (0x%08X)\n", iStatus);
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: MYAPP_InitPipe
**
** Purpose: To initialize all message pipes and subscribe to messages for MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_CreatePipe
**    CFE_SB_Subscribe
**    CFE_ES_WriteToSysLog
**
** Called By:
**    MYAPP_InitApp
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_MYAPP_AppData.usSchPipeDepth
**    g_MYAPP_AppData.cSchPipeName
**    g_MYAPP_AppData.SchPipeId
**    g_MYAPP_AppData.usCmdPipeDepth
**    g_MYAPP_AppData.cCmdPipeName
**    g_MYAPP_AppData.CmdPipeId
**    g_MYAPP_AppData.usTlmPipeDepth
**    g_MYAPP_AppData.cTlmPipeName
**    g_MYAPP_AppData.TlmPipeId
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 MYAPP_InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe */
    g_MYAPP_AppData.usSchPipeDepth = MYAPP_SCH_PIPE_DEPTH;
    memset((void*)g_MYAPP_AppData.cSchPipeName, '\0', sizeof(g_MYAPP_AppData.cSchPipeName));
    strncpy(g_MYAPP_AppData.cSchPipeName, "MYAPP_SCH_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to Wakeup messages */
    iStatus = CFE_SB_CreatePipe(&g_MYAPP_AppData.SchPipeId,
                                 g_MYAPP_AppData.usSchPipeDepth,
                                 g_MYAPP_AppData.cSchPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(MYAPP_WAKEUP_MID, g_MYAPP_AppData.SchPipeId, CFE_SB_Default_Qos, 1);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("MYAPP - Sch Pipe failed to subscribe to MYAPP_WAKEUP_MID. (0x%08X)\n", iStatus);
            goto MYAPP_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("MYAPP - Failed to create SCH pipe (0x%08X)\n", iStatus);
        goto MYAPP_InitPipe_Exit_Tag;
    }

    /* Init command pipe */
    g_MYAPP_AppData.usCmdPipeDepth = MYAPP_CMD_PIPE_DEPTH ;
    memset((void*)g_MYAPP_AppData.cCmdPipeName, '\0', sizeof(g_MYAPP_AppData.cCmdPipeName));
    strncpy(g_MYAPP_AppData.cCmdPipeName, "MYAPP_CMD_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&g_MYAPP_AppData.CmdPipeId,
                                 g_MYAPP_AppData.usCmdPipeDepth,
                                 g_MYAPP_AppData.cCmdPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(MYAPP_CMD_MID, g_MYAPP_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("MYAPP - CMD Pipe failed to subscribe to MYAPP_CMD_MID. (0x%08X)\n", iStatus);
            goto MYAPP_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_Subscribe(MYAPP_SEND_HK_MID, g_MYAPP_AppData.CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            CFE_ES_WriteToSysLog("MYAPP - CMD Pipe failed to subscribe to MYAPP_SEND_HK_MID. (0x%08X)\n", iStatus);
            goto MYAPP_InitPipe_Exit_Tag;
        }
        
    }
    else
    {
        CFE_ES_WriteToSysLog("MYAPP - Failed to create CMD pipe (0x%08X)\n", iStatus);
        goto MYAPP_InitPipe_Exit_Tag;
    }

    /* Init telemetry pipe */
    g_MYAPP_AppData.usTlmPipeDepth = MYAPP_TLM_PIPE_DEPTH;
    memset((void*)g_MYAPP_AppData.cTlmPipeName, '\0', sizeof(g_MYAPP_AppData.cTlmPipeName));
    strncpy(g_MYAPP_AppData.cTlmPipeName, "MYAPP_TLM_PIPE", OS_MAX_API_NAME-1);

    /* Subscribe to telemetry messages on the telemetry pipe */
    iStatus = CFE_SB_CreatePipe(&g_MYAPP_AppData.TlmPipeId,
                                 g_MYAPP_AppData.usTlmPipeDepth,
                                 g_MYAPP_AppData.cTlmPipeName);
    if (iStatus == CFE_SUCCESS)
    {
        /* TODO:  Add CFE_SB_Subscribe() calls for other apps' output data here.
        **
        ** Examples:
        **     CFE_SB_Subscribe(GNCEXEC_OUT_DATA_MID, g_MYAPP_AppData.TlmPipeId);
        */
    }
    else
    {
        CFE_ES_WriteToSysLog("MYAPP - Failed to create TLM pipe (0x%08X)\n", iStatus);
        goto MYAPP_InitPipe_Exit_Tag;
    }

MYAPP_InitPipe_Exit_Tag:
    return (iStatus);
}
    
/*=====================================================================================
** Name: MYAPP_InitData
**
** Purpose: To initialize global variables used by MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_SB_InitMsg
**
** Called By:
**    MYAPP_InitApp
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    g_MYAPP_AppData.InData
**    g_MYAPP_AppData.OutData
**    g_MYAPP_AppData.HkTlm
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 MYAPP_InitData()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init input data */
    memset((void*)&g_MYAPP_AppData.InData, 0x00, sizeof(g_MYAPP_AppData.InData));

    /* Init output data */
    memset((void*)&g_MYAPP_AppData.OutData, 0x00, sizeof(g_MYAPP_AppData.OutData));
    CFE_SB_InitMsg(&g_MYAPP_AppData.OutData,
                   MYAPP_OUT_DATA_MID, sizeof(g_MYAPP_AppData.OutData), TRUE);

    /* Init housekeeping packet */
    memset((void*)&g_MYAPP_AppData.HkTlm, 0x00, sizeof(g_MYAPP_AppData.HkTlm));
    CFE_SB_InitMsg(&g_MYAPP_AppData.HkTlm,
                   MYAPP_HK_TLM_MID, sizeof(g_MYAPP_AppData.HkTlm), TRUE);

    return (iStatus);
}
    
/*=====================================================================================
** Name: MYAPP_InitApp
**
** Purpose: To initialize all data local to and used by MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_WriteToSysLog
**    CFE_EVS_SendEvent
**    OS_TaskInstallDeleteHandler
**    MYAPP_InitEvent
**    MYAPP_InitPipe
**    MYAPP_InitData
**
** Called By:
**    MYAPP_AppMain
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 MYAPP_InitApp()
{
    int32  iStatus=CFE_SUCCESS;

    g_MYAPP_AppData.uiRunStatus = CFE_ES_APP_RUN;

    iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("MYAPP - Failed to register the app (0x%08X)\n", iStatus);
        goto MYAPP_InitApp_Exit_Tag;
    }

    if ((MYAPP_InitEvent() != CFE_SUCCESS) || 
        (MYAPP_InitPipe() != CFE_SUCCESS) || 
        (MYAPP_InitData() != CFE_SUCCESS))
    {
        iStatus = -1;
        goto MYAPP_InitApp_Exit_Tag;
    }

    /* Install the cleanup callback */
    OS_TaskInstallDeleteHandler((void*)&MYAPP_CleanupCallback);

MYAPP_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(MYAPP_INIT_INF_EID, CFE_EVS_INFORMATION,
                          "MYAPP - Application initialized");
    }
    else
    {
        CFE_ES_WriteToSysLog("MYAPP - Application failed to initialize\n");
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: MYAPP_CleanupCallback
**
** Purpose: To handle any neccesary cleanup prior to application exit
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_CleanupCallback()
{
    /* TODO:  Add code to cleanup memory and other cleanup here */
}
    
/*=====================================================================================
** Name: MYAPP_RcvMsg
**
** Purpose: To receive and process messages for MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    int32 iStatus - Status of initialization 
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    MYAPP_ProcessNewCmds
**    MYAPP_ProcessNewData
**    MYAPP_SendOutData
**
** Called By:
**    MYAPP_Main
**
** Global Inputs/Reads:
**    g_MYAPP_AppData.SchPipeId
**
** Global Outputs/Writes:
**    g_MYAPP_AppData.uiRunStatus
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
int32 MYAPP_RcvMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MYAPP_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, g_MYAPP_AppData.SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MYAPP_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
	{
            case MYAPP_WAKEUP_MID:
                MYAPP_ProcessNewCmds();
                MYAPP_ProcessNewData();

                /* TODO:  Add more code here to handle other things when app wakes up */

                /* The last thing to do at the end of this Wakeup cycle should be to
                   automatically publish new output. */
                MYAPP_SendOutData();
                break;

            default:
                CFE_EVS_SendEvent(MYAPP_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "MYAPP - Recvd invalid SCH msgId (0x%08X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* If there's no incoming message, you can do something here, or nothing */
    }
    else
    {
        /* This is an example of exiting on an error.
        ** Note that a SB read error is not always going to result in an app quitting.
        */
        CFE_EVS_SendEvent(MYAPP_PIPE_ERR_EID, CFE_EVS_ERROR,
			  "MYAPP: SB pipe read error (0x%08X), app will exit", iStatus);
        g_MYAPP_AppData.uiRunStatus= CFE_ES_APP_ERROR;
    }

    return (iStatus);
}
    
/*=====================================================================================
** Name: MYAPP_ProcessNewData
**
** Purpose: To process incoming data subscribed by MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**
** Called By:
**    MYAPP_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_ProcessNewData()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   TlmMsgPtr=NULL;
    CFE_SB_MsgId_t  TlmMsgId;

    /* Process telemetry messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&TlmMsgPtr, g_MYAPP_AppData.TlmPipeId, CFE_SB_POLL);
        if (iStatus == CFE_SUCCESS)
        {
            TlmMsgId = CFE_SB_GetMsgId(TlmMsgPtr);
            switch (TlmMsgId)
            {
                /* TODO:  Add code to process all subscribed data here 
                **
                ** Example:
                **     case NAV_OUT_DATA_MID:
                **         MYAPP_ProcessNavData(TlmMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(MYAPP_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "MYAPP - Recvd invalid TLM msgId (0x%08X)", TlmMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(MYAPP_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "MYAPP: CMD pipe read error (0x%08X)", iStatus);
            g_MYAPP_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: MYAPP_ProcessNewCmds
**
** Purpose: To process incoming command messages for MYAPP application
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_RcvMsg
**    CFE_SB_GetMsgId
**    CFE_EVS_SendEvent
**    MYAPP_ProcessNewAppCmds
**    MYAPP_ReportHousekeeping
**
** Called By:
**    MYAPP_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    None
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_ProcessNewCmds()
{
    int iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages till the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, g_MYAPP_AppData.CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case MYAPP_CMD_MID:
                    MYAPP_ProcessNewAppCmds(CmdMsgPtr);
                    break;

                case MYAPP_SEND_HK_MID:
                    MYAPP_ReportHousekeeping();
                    break;

                /* TODO:  Add code to process other subscribed commands here
                **
                ** Example:
                **     case CFE_TIME_DATA_CMD_MID:
                **         MYAPP_ProcessTimeDataCmd(CmdMsgPtr);
                **         break;
                */

                default:
                    CFE_EVS_SendEvent(MYAPP_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "MYAPP - Recvd invalid CMD msgId (0x%08X)", CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            CFE_EVS_SendEvent(MYAPP_PIPE_ERR_EID, CFE_EVS_ERROR,
                  "MYAPP: CMD pipe read error (0x%08X)", iStatus);
            g_MYAPP_AppData.uiRunStatus = CFE_ES_APP_ERROR;
            break;
        }
    }
}
    
/*=====================================================================================
** Name: MYAPP_ProcessNewAppCmds
**
** Purpose: To process command messages targeting MYAPP application
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr - new command message pointer
**
** Returns:
**    None
**
** Routines Called:
**    CFE_SB_GetCmdCode
**    CFE_EVS_SendEvent
**
** Called By:
**    MYAPP_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    g_MYAPP_AppData.HkTlm.usCmdCnt
**    g_MYAPP_AppData.HkTlm.usCmdErrCnt
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_ProcessNewAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case MYAPP_NOOP_CC:
                g_MYAPP_AppData.HkTlm.usCmdCnt++;
                CFE_EVS_SendEvent(MYAPP_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "MYAPP - Recvd NOOP cmd (%d)", uiCmdCode);
                break;

            case MYAPP_RESET_CC:
                g_MYAPP_AppData.HkTlm.usCmdCnt = 0;
                g_MYAPP_AppData.HkTlm.usCmdErrCnt = 0;
                CFE_EVS_SendEvent(MYAPP_CMD_INF_EID, CFE_EVS_INFORMATION,
                                  "MYAPP - Recvd RESET cmd (%d)", uiCmdCode);
                break;

            /* TODO:  Add code to process the rest of the MYAPP commands here */

            default:
                g_MYAPP_AppData.HkTlm.usCmdErrCnt++;
                CFE_EVS_SendEvent(MYAPP_MSGID_ERR_EID, CFE_EVS_ERROR,
                                  "MYAPP - Recvd invalid cmdId (%d)", uiCmdCode);
                break;
        }
    }
}
    
/*=====================================================================================
** Name: MYAPP_ReportHousekeeping
**
** Purpose: To send housekeeping message
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    MYAPP_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  GSFC, CSDC
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_ReportHousekeeping()
{
    /* TODO:  Add code to update housekeeping data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_MYAPP_AppData.HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_MYAPP_AppData.HkTlm);
}
    
/*=====================================================================================
** Name: MYAPP_SendOutData
**
** Purpose: To publish 1-Wakeup cycle output data
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    TBD
**
** Called By:
**    MYAPP_RcvMsg
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_SendOutData()
{
    /* TODO:  Add code to update output data, if needed, here.  */

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&g_MYAPP_AppData.OutData);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&g_MYAPP_AppData.OutData);
}
    
/*=====================================================================================
** Name: MYAPP_VerifyCmdLength
**
** Purpose: To verify command length for a particular command message
**
** Arguments:
**    CFE_SB_Msg_t*  MsgPtr      - command message pointer
**    uint16         usExpLength - expected command length
**
** Returns:
**    boolean bResult - result of verification
**
** Routines Called:
**    TBD
**
** Called By:
**    MYAPP_ProcessNewCmds
**
** Global Inputs/Reads:
**    None
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
boolean MYAPP_VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult=FALSE;
    uint16  usMsgLen=0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            CFE_EVS_SendEvent(MYAPP_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "MYAPP - Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            g_MYAPP_AppData.HkTlm.usCmdErrCnt++;
        }
    }

    return (bResult);
}
    
/*=====================================================================================
** Name: MYAPP_AppMain
**
** Purpose: To define MYAPP application's entry point and main process loop
**
** Arguments:
**    None
**
** Returns:
**    None
**
** Routines Called:
**    CFE_ES_RegisterApp
**    CFE_ES_RunLoop
**    CFE_ES_PerfLogEntry
**    CFE_ES_PerfLogExit
**    CFE_ES_ExitApp
**    CFE_ES_WaitForStartupSync
**    MYAPP_InitApp
**    MYAPP_RcvMsg
**
** Called By:
**    TBD
**
** Global Inputs/Reads:
**    TBD
**
** Global Outputs/Writes:
**    TBD
**
** Limitations, Assumptions, External Events, and Notes:
**    1. List assumptions that are made that apply to this function.
**    2. List the external source(s) and event(s) that can cause this function to execute.
**    3. List known limitations that apply to this function.
**    4. If there are no assumptions, external events, or notes then enter NONE.
**       Do not omit the section.
**
** Algorithm:
**    Psuedo-code or description of basic algorithm
**
** Author(s):  CSDC 
**
** History:  Date Written  2016-11-08
**           Unit Tested   yyyy-mm-dd
**=====================================================================================*/
void MYAPP_AppMain()
{
    /* Register the application with Executive Services */
    CFE_ES_RegisterApp();

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(MYAPP_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (MYAPP_InitApp() != CFE_SUCCESS)
    {
        g_MYAPP_AppData.uiRunStatus = CFE_ES_APP_ERROR;
    } else {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(MYAPP_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(MYAPP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(MYAPP_MAIN_TASK_PERF_ID);
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&g_MYAPP_AppData.uiRunStatus) == TRUE)
    {
        MYAPP_RcvMsg(CFE_SB_PEND_FOREVER);
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(MYAPP_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(g_MYAPP_AppData.uiRunStatus);
} 
    
/*=======================================================================================
** End of file myapp_app.c
**=====================================================================================*/
    