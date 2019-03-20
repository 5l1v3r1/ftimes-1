/*
 ***********************************************************************
 *
 * $Id: fsinfo.h,v 1.1.1.1 2002/01/18 03:17:32 mavrik Exp $
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
#define FSINFO_MAX_STRING 255

enum eFSTypes
{
  FSTYPE_UNSUPPORTED = 0,
  FSTYPE_NA,
  FSTYPE_EXT2,
  FSTYPE_FAT,
  FSTYPE_FAT_REMOTE,
  FSTYPE_NFS,
  FSTYPE_NTFS, 
  FSTYPE_NTFS_REMOTE,
  FSTYPE_TMP,
  FSTYPE_UFS,
  FSTYPE_AIX,
  FSTYPE_JFS,
  FSTYPE_NFS3,
  FSTYPE_FFS
};


/*-
 ***********************************************************************
 *
 * Platform Specific Defines
 *
 ***********************************************************************
 */
#ifdef FTimes_AIX
#ifndef MNT_AIX
#define MNT_AIX      0       /* AIX physical fs "oaix"         */
#endif
#ifndef MNT_NFS
#define MNT_NFS      2       /* SUN Network File System "nfs"  */
#endif
#ifndef MNT_JFS
#define MNT_JFS      3       /* AIX R3 physical fs "jfs"       */
#endif
#ifndef MNT_CDROM
#define MNT_CDROM    5       /* CDROM File System "cdrom"      */
#endif
#ifndef MNT_SFS
#define MNT_SFS     16       /* AIX Special FS (STREAM mounts) */
#endif
#ifndef MNT_CACHEFS
#define MNT_CACHEFS 17       /* Cachefs file system            */
#endif
#ifndef MNT_NFS3
#define MNT_NFS3    18       /* NFSv3 file system              */
#endif
#ifndef MNT_AUTOFS
#define MNT_AUTOFS  19       /* Automount file system          */
#endif
#endif

#ifdef FTimes_LINUX
#ifndef EXT2_OLD_SUPER_MAGIC
#define EXT2_OLD_SUPER_MAGIC  0xEF51
#endif
#ifndef EXT2_SUPER_MAGIC
#define EXT2_SUPER_MAGIC      0xEF53
#endif
#ifndef ISOFS_SUPER_MAGIC
#define ISOFS_SUPER_MAGIC     0x9660
#endif
#ifndef MSDOS_SUPER_MAGIC
#define MSDOS_SUPER_MAGIC     0x4d44
#endif
#ifndef NFS_SUPER_MAGIC
#define NFS_SUPER_MAGIC       0x6969
#endif
#ifndef PROC_SUPER_MAGIC
#define PROC_SUPER_MAGIC      0x9fa0
#endif
#ifndef UFS_MAGIC
#define UFS_MAGIC         0x00011954
#endif
#endif


/*-
 ***********************************************************************
 *
 * Function Prototypes
 *
 ***********************************************************************
 */
int                 GetFileSystemType(char *path, char *ebuf);


/*-
 ***********************************************************************
 *
 * External Variables
 *
 ***********************************************************************
 */
extern char         FSType[][FSINFO_MAX_STRING];