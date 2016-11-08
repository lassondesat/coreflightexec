/*=======================================================================================
** File Name:  myapp_private_types.h
**
** Title:  Type Header File for MYAPP Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  This header file contains declarations and definitions of all MYAPP's private
**           data structures and data types.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _MYAPP_PRIVATE_TYPES_H_
#define _MYAPP_PRIVATE_TYPES_H_

/*
** Pragmas
*/

/*
** Include Files
*/
#include "cfe.h"

/*
** Local Defines
*/

/*
** Local Structure Declarations
*/

typedef struct
{
    uint8  ucCmdHeader[CFE_SB_CMD_HDR_SIZE];
} MYAPP_NoArgCmd_t;


typedef struct
{
    uint32  counter;

    /* TODO:  Add input data to this application here, such as raw data read from I/O
    **        devices or data subscribed from other apps' output data.
    */

} MYAPP_InData_t;

typedef struct
{
    uint8   ucTlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint32  uiCounter;
} MYAPP_OutData_t;

/* TODO:  Add more private structure definitions here, if necessary. */

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

#endif /* _MYAPP_PRIVATE_TYPES_H_ */

/*=======================================================================================
** End of file myapp_private_types.h
**=====================================================================================*/
    