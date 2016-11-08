/*=======================================================================================
** File Name:  serial_msg.h
**
** Title:  Message Definition Header File for SERIAL Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  To define SERIAL's command and telemetry message defintions 
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _SERIAL_MSG_H_
#define _SERIAL_MSG_H_

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
** SERIAL command codes
*/
#define SERIAL_NOOP_CC                 0
#define SERIAL_RESET_CC                1

/*
** Local Structure Declarations
*/
typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;
    uint8              usCmdErrCnt;

    /* TODO:  Add declarations for additional housekeeping data here */

} SERIAL_HkTlm_t;


#endif /* _SERIAL_MSG_H_ */

/*=======================================================================================
** End of file serial_msg.h
**=====================================================================================*/
    