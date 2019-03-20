/*-
 ***********************************************************************
 *
 * $Id: message.h,v 1.18 2013/02/14 16:55:20 mavrik Exp $
 *
 ***********************************************************************
 *
 * Copyright 2000-2013 The FTimes Project, All Rights Reserved.
 *
 ***********************************************************************
 */
#ifndef _MESSAGE_H_INCLUDED
#define _MESSAGE_H_INCLUDED

/*-
 ***********************************************************************
 *
 * Defines
 *
 ***********************************************************************
 */
#define MESSAGE_AUTO_FLUSH_OFF 0
#define MESSAGE_AUTO_FLUSH_ON  1
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
#define MESSAGE_WARNING_STRING  "***  LOG_WARN  ***"
#define MESSAGE_FAILURE_STRING  "***  LOG_FAIL  ***"
#define MESSAGE_CRITICAL_STRING "***  LOG_CRIT  ***"
#if defined(USE_FILE_HOOKS)
#define MESSAGE_HOOK_STRING     "***  LOG_HOOK  ***"
#endif

/*-
 ***********************************************************************
 *
 * Function Prototypes
 *
 ***********************************************************************
 */
void                MessageHandler(int iAction, int iLevel, char *pcCode, char *pcMessage);
void                MessageSetAutoFlush(int iOnOff);
void                MessageSetLogLevel(int iLevel);
void                MessageSetNewLine(char *pcNewLine);
void                MessageSetOutputStream(FILE *pFile);

#endif /* !_MESSAGE_H_INCLUDED */
