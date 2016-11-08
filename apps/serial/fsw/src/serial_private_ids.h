/*=======================================================================================
** File Name:  serial_private_ids.h
**
** Title:  ID Header File for SERIAL Application
**
** $Author:    CSDC
** $Revision: 1.1 $
** $Date:      2016-11-08
**
** Purpose:  This header file contains declarations and definitions of SERIAL's private IDs.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2016-11-08 | CSDC | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _SERIAL_PRIVATE_IDS_H_
#define _SERIAL_PRIVATE_IDS_H_

/*
** Pragmas
*/

/*
** Include Files
*/

/*
** Local Defines
*/

/* Event IDs */
#define SERIAL_RESERVED_EID  0

#define SERIAL_INF_EID        1
#define SERIAL_INIT_INF_EID   2
#define SERIAL_ILOAD_INF_EID  3
#define SERIAL_CDS_INF_EID    4
#define SERIAL_CMD_INF_EID    5

#define SERIAL_ERR_EID         51
#define SERIAL_INIT_ERR_EID    52
#define SERIAL_ILOAD_ERR_EID   53
#define SERIAL_CDS_ERR_EID     54
#define SERIAL_CMD_ERR_EID     55
#define SERIAL_PIPE_ERR_EID    56
#define SERIAL_MSGID_ERR_EID   57
#define SERIAL_MSGLEN_ERR_EID  58

#define SERIAL_EVT_CNT  14

/*
** Local Structure Declarations
*/

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

#endif /* _SERIAL_PRIVATE_IDS_H_ */

/*=======================================================================================
** End of file serial_private_ids.h
**=====================================================================================*/
    