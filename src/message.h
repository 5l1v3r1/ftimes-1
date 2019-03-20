/*
 ***********************************************************************
 *
 * $Id: message.h,v 1.1.1.1 2002/01/18 03:17:32 mavrik Exp $
 *
 ***********************************************************************
 *
 * Copyright 2000-2002 Klayton Monroe, Exodus Communications, Inc.
 * All Rights Reserved.
 *
 ***********************************************************************
 */

/*-
 ***********************************************************************
 *
 * Defines
 *
 ***********************************************************************
 */
#define MESSAGE_QUEUE_IT       0
#define MESSAGE_FLUSH_IT       1
#define MESSAGE_QUEUE_LENGTH 100
#define MESSAGE_SIZE        1024
#define MESSAGE_WIDTH         18

#define MESSAGE_DEBUGGER       0
#define MESSAGE_WAYPOINT       1
#define MESSAGE_LANDMARK       2
#define MESSAGE_INFORMATION    3
#define MESSAGE_WARNING        4
#define MESSAGE_FAILURE        5
#define MESSAGE_CRITICAL       6
#define MESSAGE_ALWAYSON       7

#define MESSAGE_DEBUGGER_STRING "@@@  DEBUGGER  @@@"
#define MESSAGE_WAYPOINT_STRING "---  WAYPOINT  ---"
#define MESSAGE_LANDMARK_STRING "+++  LANDMARK  +++"
#define MESSAGE_PROPERTY_STRING "<<<  PROPERTY  >>>"
#define MESSAGE_MODEDATA_STRING "<<<  MODEDATA  >>>"
#define MESSAGE_EXECDATA_STRING "<<<  EXECDATA  >>>"
#define MESSAGE_WARNING_STRING  "***  ER->WARN  ***"
#define MESSAGE_FAILURE_STRING  "***  ER->FAIL  ***"
#define MESSAGE_CRITICAL_STRING "***  ER->CRIT  ***"


/*-
 ***********************************************************************
 *
 * Function Prototypes
 *
 ***********************************************************************
 */
void                MessageHandler(int iAction, int iLevel, char *pcCode, char *pcMessage);
void                MessageSetLogLevel(int iLevel);
void                MessageSetNewLine(char *pcNewLine);
void                MessageSetOutputStream(FILE *pFile);