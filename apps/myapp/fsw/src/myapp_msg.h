/*=======================================================================================
** File Name:  myapp_msg.h
**
** Title:  Message Definition Header File for MYAPP Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  To define MYAPP's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _MYAPP_MSG_H_
#define _MYAPP_MSG_H_

/*
** Pragmas
*/

/*
** Include Files
*/



/*
** Local Defines
*/

/*
** MYAPP command codes
*/
#define MYAPP_NOOP_CC                 0
#define MYAPP_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} MYAPP_HkTlm_t;


#endif /* _MYAPP_MSG_H_ */

/*=======================================================================================
** End of file myapp_msg.h
**=====================================================================================*/
    