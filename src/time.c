/*
 ***********************************************************************
 *
 * $Id: time.c,v 1.1.1.1 2002/01/18 03:17:24 mavrik Exp $
 *
 ***********************************************************************
 *
 * Copyright 2000-2002 Klayton Monroe, Exodus Communications, Inc.
 * All Rights Reserved.
 *
 ***********************************************************************
 */

#include "all-includes.h"

/*-
 ***********************************************************************
 *
 * TimeGetTime
 *
 ***********************************************************************
 */
time_t
TimeGetTime(char *pcDate, char *pcTime, char *zonebuf, char *pcDateTime)
{
  int                 iCount;
  time_t              timeValue;

  if ((timeValue = time(NULL)) < 0)
  {
    return ER;
  }

  if (pcTime != NULL)
  {
    iCount = strftime(pcTime, FTIMES_TIME_SIZE, FTIMES_RUNTIME_FORMAT, localtime(&timeValue));
    if (iCount < 0 || iCount > FTIMES_TIME_SIZE - 1)
    {
      return ER;
    }
  }

  if (pcDate != NULL)
  {
    iCount = strftime(pcDate, FTIMES_TIME_SIZE, FTIMES_RUNDATE_FORMAT, localtime(&timeValue));
    if (iCount < 0 || iCount > FTIMES_TIME_SIZE - 1)
    {
      return ER;
    }
  }

  if (zonebuf != NULL)
  {
    iCount = strftime(zonebuf, FTIMES_ZONE_SIZE, FTIMES_RUNZONE_FORMAT, localtime(&timeValue));
    if (iCount < 0 || iCount > FTIMES_ZONE_SIZE - 1)
    {
      return ER;
    }
  }

  /*-
   *********************************************************************
   *
   * As a matter of convention, datetime values are in GMT. This
   * prevents confusion with filenames and Integrity Server
   * transactions. If localtime was used instead, then issues with
   * things like Daylight Savings Time can arise. For example, when
   * Daylight Savings Time falls back, it is possible to clobber
   * old output files because there would be an hour of time for
   * which output filenames could match existing names.
   *
   *********************************************************************
   */
  if (pcDateTime != NULL)
  {
    iCount = strftime(pcDateTime, FTIMES_TIME_SIZE, "%Y%m%d%H%M%S", gmtime(&timeValue));
    if (iCount < 0 || iCount > FTIMES_TIME_SIZE - 1)
    {
      return ER;
    }
  }

  return timeValue;
}


#ifdef FTimes_UNIX
/*-
 ***********************************************************************
 *
 * TimeFormatTime
 *
 ***********************************************************************
 */
int
TimeFormatTime(time_t *ptimeValue, char *pcTime)
{
  int                 iCount;

  /*-
   *********************************************************************
   *
   * Constraint all time stamps are relative to GMT. In practice, this
   * means we use gmtime instead of localtime.
   *
   *********************************************************************
   */

  pcTime[0] = 0;

  iCount = strftime(pcTime, FTIMES_TIME_SIZE, FTIMES_TIME_FORMAT, gmtime(ptimeValue));

  if (iCount != FTIMES_TIME_FORMAT_SIZE - 1)
  {
    return ER;
  }

  return ER_OK;
}
#endif


#ifdef FTimes_WIN32
/*-
 ***********************************************************************
 *
 * TimeFormatTime
 *
 ***********************************************************************
 */
int
TimeFormatTime(FILETIME *pFileTime, char *pcTime)
{
  int                 iCount;
  SYSTEMTIME          systemTime;

  pcTime[0] = 0;

  if (!FileTimeToSystemTime(pFileTime, &systemTime))
  {
    return ER;
  }

  iCount = snprintf(pcTime, FTIMES_TIME_FORMAT_SIZE, FTIMES_TIME_FORMAT,
                   systemTime.wYear, systemTime.wMonth, systemTime.wDay,
                   systemTime.wHour, systemTime.wMinute, systemTime.wSecond,
                   systemTime.wMilliseconds);

  if (iCount < FTIMES_TIME_FORMAT_SIZE - 3 || iCount > FTIMES_TIME_FORMAT_SIZE - 1)
  {
    return ER;
  }

  return ER_OK;
}


/*-
 ***********************************************************************
 *
 * TimeFormatOutOfBandTime
 *
 ***********************************************************************
 */
int
TimeFormatOutOfBandTime(FILETIME *pFileTime, char *pcTime)
{
  int                 iCount;
  SYSTEMTIME          systemTime;

  pcTime[0] = 0;

  if (!FileTimeToSystemTime(pFileTime, &systemTime))
  {
    return ER;
  }

  iCount = snprintf(pcTime, FTIMES_OOB_TIME_FORMAT_SIZE, FTIMES_OOB_TIME_FORMAT,
                   systemTime.wYear, systemTime.wMonth, systemTime.wDay,
                   systemTime.wHour, systemTime.wMinute, systemTime.wSecond,
                   systemTime.wMilliseconds);

  if (iCount < FTIMES_OOB_TIME_FORMAT_SIZE - 3 || iCount > FTIMES_OOB_TIME_FORMAT_SIZE - 1)
  {
    return ER;
  }

  return ER_OK;
}
#endif