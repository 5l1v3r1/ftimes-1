/*
 ***********************************************************************
 *
 * $Id: pool2string.c,v 1.1 2002/09/20 17:52:42 mavrik Exp $
 *
 ***********************************************************************
 *
 * Copyright 2002 Klayton Monroe, Exodus Communications, Inc.
 * All Rights Reserved.
 *
 ***********************************************************************
 */
#include <stdio.h>
#include "pool2string.h"


/*-
 ***********************************************************************
 *
 * Main
 *
 ***********************************************************************
 */
int
main()
{
  unsigned char aucPool[POOL2STRING_POOL_SIZE];
  unsigned char aucTaps[POOL2STRING_POOL_TAPS];
  
  POOL2STRING_NEW_POOL(aucPool, POOL2STRING_POOL_SIZE, POOL2STRING_POOL_SEED);
  POOL2STRING_TAP_POOL(aucTaps, aucPool);
  printf("String='%s'\n", aucTaps);
  return 0;
}
