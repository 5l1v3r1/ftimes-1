/*-
 ***********************************************************************
 *
 * $Id: xmagic.h,v 1.66 2012/05/04 17:43:12 mavrik Exp $
 *
 ***********************************************************************
 *
 * Copyright 2000-2012 The FTimes Project, All Rights Reserved.
 *
 ***********************************************************************
 */
#ifndef _XMAGIC_H_INCLUDED
#define _XMAGIC_H_INCLUDED

/*-
 ***********************************************************************
 *
 * Defines
 *
 ***********************************************************************
 */
#ifdef UNIX
#define XMAGIC_DEFAULT_LOCATION XMAGIC_PREFIX"/etc/xmagic"
#define XMAGIC_CURRENT_LOCATION "./xmagic"
#endif

#ifdef WIN32
#define XMAGIC_DEFAULT_LOCATION XMAGIC_PREFIX"\\etc\\xmagic"
#define XMAGIC_CURRENT_LOCATION ".\\xmagic"
#endif

#define XMAGIC_DEFAULT     "other/unknown"
#define XMAGIC_ISEMPTY       "other/empty"

#define XMAGIC_COMBO_SIZE ((7 + 1) * (XMAGIC_COMBO_SLOT_COUNT)) /* (strlen("100.00/") + 1 for the NULL byte) * XMAGIC_COMBO_SLOT_COUNT */
#define XMAGIC_COMBO_SLOT_COUNT 10

#define XMAGIC_PERCENT_COMBO_CSPDAE_SLOTS 6

#define XMAGIC_PERCENT_1BYTE_CODES    256
#define XMAGIC_ROW_AVERAGE_1_CODES    256
#define XMAGIC_ROW_AVERAGE_2_CODES  65536
#define XMAGIC_ROW_ENTROPY_1_CODES    256
#define XMAGIC_ROW_ENTROPY_2_CODES  65536
#define XMAGIC_LOG2_OF_10 3.32192809488736234787 /* log2(10) = ln(10)/ln(2) */
#define XMAGIC_LSB                      0
#define XMAGIC_MSB                      1
#define XMAGIC_READ_BUFSIZE        0x4000
#define XMAGIC_MAX_HASH_LENGTH ((SHA256_HASH_SIZE)*2)
#define XMAGIC_MAX_LINE              8192
#define XMAGIC_MAX_LEVEL              128
#define XMAGIC_STRING_BUFSIZE          64
#define XMAGIC_SUBJECT_BUFSIZE        128
#ifdef USE_PCRE
#define XMAGIC_REGEXP_CAPTURE_BUFSIZE XMAGIC_SUBJECT_BUFSIZE
#define XMAGIC_REGEXP_BUFSIZE        1024
#endif
#define XMAGIC_DESCRIPTION_BUFSIZE    256

#define XMAGIC_INDIRECT_OFFSET 0x00000001
#define XMAGIC_RELATIVE_OFFSET 0x00000002
#define XMAGIC_NO_SPACE        0x00000004
#define XMAGIC_HAVE_WARP       0x00000008
#define XMAGIC_HAVE_SIZE       0x00000010
#define XMAGIC_RELATIVE_X_OFFSET 0x00000020

#define XMAGIC_TEST_ERROR              -1
#define XMAGIC_TEST_FALSE               0
#define XMAGIC_TEST_MATCH               1

#ifdef USE_PCRE
#ifndef PCRE_MAX_CAPTURE_COUNT
#define PCRE_MAX_CAPTURE_COUNT 9 /* This is the maximum number of capturing '()' subpatterns allowed. */
#endif
/*
 * The following quote was taken from pcreapi(3) man page.
 *
 *   The smallest size for ovector that will allow for n captured
 *   substrings, in addition to the  offsets of the substring matched
 *   by the whole pattern, is (n+1)*3.
 *
 */
#ifndef PCRE_OVECTOR_ARRAY_SIZE
#define PCRE_OVECTOR_ARRAY_SIZE 30
#endif
#endif

/*-
 ***********************************************************************
 *
 * Typedefs
 *
 ***********************************************************************
 */
typedef enum _XMAGIC_TEST_OPERATORS
{
  XMAGIC_OP_AND = 0,   /* '&'         */
  XMAGIC_OP_EQ,        /* '==' or '=' */
  XMAGIC_OP_GE,        /* '>='        */
  XMAGIC_OP_GE_AND_LE, /* '[]'        */
  XMAGIC_OP_GE_AND_LT, /* '[)'        */
  XMAGIC_OP_GT,        /* '>'         */
  XMAGIC_OP_GT_AND_LE, /* '(]'        */
  XMAGIC_OP_GT_AND_LT, /* '()'        */
  XMAGIC_OP_LE,        /* '<='        */
  XMAGIC_OP_LE_OR_GE,  /* ']['        */
  XMAGIC_OP_LE_OR_GT,  /* ']('        */
  XMAGIC_OP_LT,        /* '<'         */
  XMAGIC_OP_LT_OR_GE,  /* ')['        */
  XMAGIC_OP_LT_OR_GT,  /* ')('        */
  XMAGIC_OP_NE,        /* '!=' or '!' */
  XMAGIC_OP_NOOP,      /* 'x'         */
#ifdef USE_PCRE
  XMAGIC_OP_REGEXP_EQ, /* '=~'        */
  XMAGIC_OP_REGEXP_NE, /* '!~'        */
#endif
  XMAGIC_OP_XOR,       /* '^'         */
} XMAGIC_TEST_OPERATORS;

typedef enum _XMAGIC_WARP_OPERATORS
{
  XMAGIC_WARP_OP_MOD = 1,      /* '%' */
  XMAGIC_WARP_OP_AND,          /* '&' */
  XMAGIC_WARP_OP_MUL,          /* '*' */
  XMAGIC_WARP_OP_ADD,          /* '+' */
  XMAGIC_WARP_OP_SUB,          /* '-' */
  XMAGIC_WARP_OP_DIV,          /* '/' */
  XMAGIC_WARP_OP_LSHIFT,       /* '<' */
  XMAGIC_WARP_OP_RSHIFT,       /* '>' */
  XMAGIC_WARP_OP_XOR,          /* '^' */
  XMAGIC_WARP_OP_OR,           /* '|' */
} XMAGIC_WARP_OPERATORS;

typedef enum _XMAGIC_TYPES
{
  XMAGIC_BEDATE = 1,
  XMAGIC_BELONG,
  XMAGIC_BESHORT,
  XMAGIC_BEUI64,
  XMAGIC_BYTE,
  XMAGIC_DATE,
  XMAGIC_LEDATE,
  XMAGIC_LELONG,
  XMAGIC_LESHORT,
  XMAGIC_LEUI64,
  XMAGIC_LONG,
  XMAGIC_MD5,
  XMAGIC_NLEFT,
#ifdef USE_PCRE
  XMAGIC_REGEXP,
#endif
  XMAGIC_PERCENT_COMBO_CSPDAE,
  XMAGIC_PERCENT_CTYPE_80_FF,
  XMAGIC_PERCENT_CTYPE_ALNUM,
  XMAGIC_PERCENT_CTYPE_ALPHA,
  XMAGIC_PERCENT_CTYPE_ASCII,
  XMAGIC_PERCENT_CTYPE_CNTRL,
  XMAGIC_PERCENT_CTYPE_DIGIT,
  XMAGIC_PERCENT_CTYPE_LOWER,
  XMAGIC_PERCENT_CTYPE_PRINT,
  XMAGIC_PERCENT_CTYPE_PUNCT,
  XMAGIC_PERCENT_CTYPE_SPACE,
  XMAGIC_PERCENT_CTYPE_UPPER,
  XMAGIC_PSTRING,
  XMAGIC_ROW_AVERAGE_1,
  XMAGIC_ROW_AVERAGE_2,
  XMAGIC_ROW_ENTROPY_1,
  XMAGIC_ROW_ENTROPY_2,
  XMAGIC_SHA1,
  XMAGIC_SHA256,
  XMAGIC_SHORT,
  XMAGIC_STRING,
  XMAGIC_UI64,
  XMAGIC_UNIX_YMDHMS_BEDATE,
  XMAGIC_UNIX_YMDHMS_LEDATE,
  XMAGIC_WINX_YMDHMS_BEDATE,
  XMAGIC_WINX_YMDHMS_LEDATE,
} XMAGIC_TYPES;

typedef struct _XMAGIC_INDIRECTION
{
  int                 iType;
  int                 iOperator;
  APP_UI32            ui32Value;
} XMAGIC_INDIRECTION;

typedef struct _XMAGIC_VALUE
{
  double              dLowerNumber;
  double              dNumber;
  double              dUpperNumber;
  APP_UI32            ui32LowerNumber;
  APP_UI32            ui32Number;
  APP_UI32            ui32UpperNumber;
  APP_UI64            ui64LowerNumber;
  APP_UI64            ui64Number;
  APP_UI64            ui64UpperNumber;
  APP_UI8             ui8String[XMAGIC_STRING_BUFSIZE];
} XMAGIC_VALUE;

/*-
 ***********************************************************************
 *
 * The meaning of XMAGIC...
 *
 * psParent           Pointer to parent magic
 * psSibling          Pointer to next magic
 * psChild            Pointer to subordinate magic
 * pcCombo            Pointer to the combo buffer
 * acDescription      Description to use on a match
 * iType              The type of value to examine (e.g., byte, short, long, date, etc.)
 * iTestOperator      Contains the ID of the operator (see XMAGIC_TEST_OPERATORS) used to test the value
 * iWarpOperator      Contains the ID of the operator (see XMAGIC_WARP_OPERATORS) used in the warp transformation
 * ui32FallbackCount  The number of '<'s in the test level
 * ui32Flags          Contains an OR'd set of flags that control/shape the various magic tests
 * ui32Level          The number of '>'s in the test level
 * ui32WarpValue      Contains the right-hand value used in the warp transformation
 * i32XOffset         Offset in file being evaluated (relative offsets may be negative; absolute offsets may not be negative)
 * sIndirection       A structure that contains the indirect offset information (x[.[BSLbsl]][%&*+-/<>^|][y])
 * sValue             A structure that contains the value to be tested
#ifdef USE_PCRE
 * acRegExp           User-specified regular expression
 * aucCapturedData    Captured regular expression data
 * iCaptureCount      Number of capturing ()'s in the regular expression
 * iMatchLength       Length of the captured regular expression match
 * iRegExpLength      Length of acRegExp
 * ui32Size           Size of the type in bytes (applies to entropy and regexp)
 * psPcre             Compiled regular expression
 * psPcreExtra        Results of studying the compiled regular expression
#endif
 * dAverage           Average computed over ui32Size bytes at i32XOffset
 * dEntropy           Entropy computed over ui32Size bytes at i32XOffset
 * dPercent           Percent computed over ui32Size bytes at i32XOffset
 * iStringLength      Length of sValue.ui8String
 * pcHash             Computed hash (MD5, SHA1, SHA256, etc.)
 *
 ***********************************************************************
 */
typedef struct _XMAGIC
{
  struct _XMAGIC     *psParent;
  struct _XMAGIC     *psSibling;
  struct _XMAGIC     *psChild;
  char                acDescription[XMAGIC_DESCRIPTION_BUFSIZE];
  char               *pcCombo;
  int                 iType;
  int                 iTestOperator;
  int                 iWarpOperator;
  APP_UI32            ui32FallbackCount;
  APP_UI32            ui32Flags;
  APP_UI32            ui32Level;
  APP_UI32            ui32Size;
  APP_UI32            ui32WarpValue;
  APP_SI32            i32XOffset; /* This variable can be negative for relative offsets. */
  XMAGIC_INDIRECTION  sIndirection;
  XMAGIC_VALUE        sValue;
  int                 iStringLength;
#ifdef USE_PCRE
  char                acRegExp[XMAGIC_REGEXP_BUFSIZE];
  unsigned char       aucCapturedData[XMAGIC_REGEXP_CAPTURE_BUFSIZE];
  int                 iCaptureCount;
  int                 iMatchLength;
  int                 iRegExpLength;
  pcre               *psPcre;
  pcre_extra         *psPcreExtra;
#endif
  double              dAverage;
  double              dEntropy;
  double              dPercent;
  char               *pcHash;
} XMAGIC;

/*-
 ***********************************************************************
 *
 * Function Prototypes
 *
 ***********************************************************************
 */
int                 is80_ff(int c);
double              XMagicComputePercentage(unsigned char *pucBuffer, int iLength, int iType);
char               *XMagicComputePercentageCombos(unsigned char *pucBuffer, int iLength, int iType);
double              XMagicComputeRowAverage1(unsigned char *pucBuffer, int iLength);
double              XMagicComputeRowAverage2(unsigned char *pucBuffer, int iLength);
double              XMagicComputeRowEntropy1(unsigned char *pucBuffer, int iLength);
double              XMagicComputeRowEntropy2(unsigned char *pucBuffer, int iLength);
int                 XMagicConvert2charHex(char *pcSRC, char *pcDST);
int                 XMagicConvert3charOct(char *pcSRC, char *pcDST);
int                 XMagicConvertHexToInt(int iC);
void                XMagicFormatDescription(void *pvValue, XMAGIC *psXMagic, char *pcDescription);
void                XMagicFreeXMagic(XMAGIC *psXMagic);
int                 XMagicGetDescription(char *pcS, char *pcE, XMAGIC *psXMagic, char *pcError);
int                 XMagicGetOffset(char *pcS, char *pcE, XMAGIC *psXMagic, char *pcError);
int                 XMagicGetTestOperator(char *pcS, char *pcE, XMAGIC *psXMagic, char *pcError);
int                 XMagicGetTestValue(char *pcS, char *pcE, XMAGIC *psXMagic, char *pcError);
int                 XMagicGetType(char *pcS, char *pcE, XMAGIC *psXMagic, char *pcError);
APP_SI32            XMagicGetValueOffset(unsigned char *pucBuffer, int iNRead, XMAGIC *psXMagic);
XMAGIC             *XMagicLoadMagic(char *pcFilename, char *pcError);
XMAGIC             *XMagicNewXMagic(char *pcError);
int                 XMagicParseLine(char *pcLine, XMAGIC *psXMagic, char *pcError);
int                 XMagicStringToUi64(char *pcNumber, APP_UI64 *pui64Value);
APP_UI16            XMagicSwapUi16(APP_UI16 ui16Value, APP_UI32 ui32MagicType);
APP_UI32            XMagicSwapUi32(APP_UI32 ui32Value, APP_UI32 ui32MagicType);
APP_UI64            XMagicSwapUi64(APP_UI64 ui64Value, APP_UI32 ui32MagicType);
int                 XMagicTestAverage(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
int                 XMagicTestBuffer(XMAGIC *psXMagic, unsigned char *pucBuffer, int iBufferLength, char *pcDescription, int iDescriptionLength, char *pcError);
int                 XMagicTestEntropy(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
int                 XMagicTestFile(XMAGIC *psXMagic, char *pcFilename, char *pcDescription, int iDescriptionLength, char *pcError);
int                 XMagicTestHash(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
int                 XMagicTestMagic(XMAGIC *psXMagic, unsigned char *pucBuffer, int iNRead, char *pcDescription, int *iBytesUsed, int *iBytesLeft, char *pcError);
int                 XMagicTestNumber(XMAGIC *psXMagic, APP_UI32 ui32Value);
int                 XMagicTestNumber64(XMAGIC *psXMagic, APP_UI64 ui64Value);
int                 XMagicTestPercent(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
int                 XMagicTestPercentCombo(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
#ifdef USE_PCRE
int                 XMagicTestRegExp(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
#endif
#ifdef UNIX
int                 XMagicTestSpecial(char *pcFilename, struct stat *psStatEntry, char *pcDescription, int iDescriptionLength, char *pcError);
#endif
int                 XMagicTestString(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcError);
int                 XMagicTestValue(XMAGIC *psXMagic, unsigned char *pucBuffer, int iLength, APP_SI32 iOffset, char *pcDescription, char *pcError);

#endif /* !_XMAGIC_H_INCLUDED */
