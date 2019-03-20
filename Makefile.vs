########################################################################
#
# $Id: Makefile.vs,v 1.50 2019/03/14 16:07:42 klm Exp $
#
########################################################################
#
# Copyright 2000-2019 The FTimes Project, All Rights Reserved.
#
########################################################################
#
# Purpose: Makefile for Visual Studio.
#
########################################################################

BUILD_TYPE		= RELEASE	# [RELEASE|DEBUG]
PLATFORM_TYPE		= WINNT		# [WINNT]
USE_PCRE		= Y		# [Y|N]
USE_SERVER		= N		# [Y|N]
USE_SSL			= Y		# [Y|N]
USE_STATIC_SSL_LIBS	= Y		# [Y|N]
USE_XMAGIC		= Y		# [Y|N]

INSTALL_DIR		= C:\FTimes
INSTALL_DIR_CSTRING	= C:\\FTimes
SOURCE_DIR		= src
OBJECT_DIR		= b

!IF "$(USE_PCRE)" == "Y" || "$(USE_PCRE)" == "y"
PCRE_DIR		= C:\Pcre
PCRE_LIB_DIR		= $(PCRE_DIR)\lib
PCRE_INC_DIR		= $(PCRE_DIR)\include
PCRE_COMPILER_FLAGS	= /D USE_PCRE /D PCRE_STATIC /I"$(PCRE_INC_DIR)"
PCRE_LINKER_FLAGS	= /libpath:"$(PCRE_LIB_DIR)" pcre.lib pcreposix.lib
!ENDIF

!IF "$(USE_SSL)" == "Y" || "$(USE_SSL)" == "y"
SSL_DIR			= C:\OpenSSL
SSL_LIB_DIR		= $(SSL_DIR)\lib
SSL_INC_DIR		= $(SSL_DIR)\include
SSL_DLL1		= $(SSL_DIR)\bin\libeay32.dll
SSL_DLL2		= $(SSL_DIR)\bin\ssleay32.dll
SSL_COMPILER_FLAGS	= /D USE_SSL /I"$(SSL_INC_DIR)"
!IF "$(USE_STATIC_SSL_LIBS)" == "Y" || "$(USE_STATIC_SSL_LIBS)" == "y"
SSL_LINKER_FLAGS	= /libpath:"$(SSL_LIB_DIR)" user32.lib advapi32.lib libeay32.lib ssleay32.lib gdi32.lib
!ELSE
SSL_LINKER_FLAGS	= /libpath:"$(SSL_LIB_DIR)" user32.lib advapi32.lib libeay32.lib ssleay32.lib
!ENDIF
!ENDIF

!IF "$(USE_STATIC_SSL_LIBS)" == "Y" || "$(USE_STATIC_SSL_LIBS)" == "y"
MTML_SWITCH		= MT
!ELSE
MTML_SWITCH		= ML
!ENDIF

!IF "$(USE_XMAGIC)" == "Y" || "$(USE_XMAGIC)" == "y"
XMAGIC_COMPILER_FLAGS	= /D USE_XMAGIC /D XMAGIC_PREFIX="""$(INSTALL_DIR_CSTRING)"""
!ENDIF

COMPILER		= cl.exe

COMPILER_FLAGS		=\
			/nologo\
			/D _MBCS\
			/D _CONSOLE\
			/D _CRT_SECURE_NO_DEPRECATE\
			/D WIN32\
			/D WINNT\
			$(PCRE_COMPILER_FLAGS)\
			$(SSL_COMPILER_FLAGS)\
			$(XMAGIC_COMPILER_FLAGS)\
			/Fo"$(OBJECT_DIR)\\"\
			/Fd"$(OBJECT_DIR)\\"\
			/Fp"$(OBJECT_DIR)\ftimes.pch"\
			/c /W3 /EHsc /FD\
!IF "$(BUILD_TYPE)" == "DEBUG" || "$(BUILD_TYPE)" == "debug"
			/D _DEBUG\
			/$(MTML_SWITCH)d /Od /Zi /Gm
!ELSE
			/D NDEBUG\
			/$(MTML_SWITCH) /O2
!ENDIF

INCLUDES		=\
			src\all-includes.h\
			src\app-includes.h\
			src\compare.h\
			src\decode.h\
			src\dig.h\
			src\error.h\
			src\fsinfo.h\
			src\ftimes.h\
			src\http.h\
			src\mask.h\
			src\md5.h\
			src\message.h\
			src\native.h\
			src\options.h\
			src\sha1.h\
			src\sha256.h\
			src\socket.h\
			src\ssl.h\
			src\ssl-pool.h\
			src\sys-includes.h\
			src\version.h\
			src\xmagic.h

OBJECTS			=\
			"$(OBJECT_DIR)\analyze.obj"\
			"$(OBJECT_DIR)\cmpmode.obj"\
			"$(OBJECT_DIR)\compare.obj"\
			"$(OBJECT_DIR)\decode.obj"\
			"$(OBJECT_DIR)\decoder.obj"\
			"$(OBJECT_DIR)\develop.obj"\
			"$(OBJECT_DIR)\dig.obj"\
			"$(OBJECT_DIR)\digmode.obj"\
			"$(OBJECT_DIR)\error.obj"\
			"$(OBJECT_DIR)\fsinfo.obj"\
			"$(OBJECT_DIR)\ftimes.obj"\
			"$(OBJECT_DIR)\getmode.obj"\
			"$(OBJECT_DIR)\http.obj"\
			"$(OBJECT_DIR)\madmode.obj"\
			"$(OBJECT_DIR)\map.obj"\
			"$(OBJECT_DIR)\mapmode.obj"\
			"$(OBJECT_DIR)\mask.obj"\
			"$(OBJECT_DIR)\md5.obj"\
			"$(OBJECT_DIR)\message.obj"\
			"$(OBJECT_DIR)\options.obj"\
			"$(OBJECT_DIR)\properties.obj"\
			"$(OBJECT_DIR)\sha1.obj"\
			"$(OBJECT_DIR)\sha256.obj"\
			"$(OBJECT_DIR)\socket.obj"\
!IF "$(USE_SSL)" == "Y" || "$(USE_SSL)" == "y"
			"$(OBJECT_DIR)\ssl.obj"\
!ENDIF
			"$(OBJECT_DIR)\support.obj"\
			"$(OBJECT_DIR)\time.obj"\
			"$(OBJECT_DIR)\url.obj"\
			"$(OBJECT_DIR)\version.obj"\
!IF "$(USE_XMAGIC)" == "Y" || "$(USE_XMAGIC)" == "y"
			"$(OBJECT_DIR)\xmagic.obj"
!ENDIF

EXECUTEABLE		= $(OBJECT_DIR)\ftimes.exe

LINKER			= link.exe

LINKER_FLAGS		=\
			/nologo\
			/subsystem:console\
			/machine:x86\
			/out:"$(EXECUTEABLE)"\
!IF "$(BUILD_TYPE)" == "DEBUG" || "$(BUILD_TYPE)" == "debug"
			/incremental:yes\
			/debug\
			/pdb:"$(OBJECT_DIR)\ftimes.pdb"\
!ELSE
			/incremental:no\
			/release\
			/pdb:none\
!ENDIF
			$(PCRE_LINKER_FLAGS) $(SSL_LINKER_FLAGS) advapi32.lib wsock32.lib ws2_32.lib

all: "$(EXECUTEABLE)"

test: "$(EXECUTEABLE)"
	utils\test_windows.bat

install: "$(EXECUTEABLE)"
	if not exist "$(INSTALL_DIR)" mkdir "$(INSTALL_DIR)"
	if not exist "$(INSTALL_DIR)\bin" mkdir "$(INSTALL_DIR)\bin"
	if not exist "$(INSTALL_DIR)\etc" mkdir "$(INSTALL_DIR)\etc"
	copy "$(EXECUTEABLE)" "$(INSTALL_DIR)\bin"
	copy etc\ftimes-dig.cfg\ftimes-dig.cfg.base "$(INSTALL_DIR)\etc\ftimes-dig.cfg.sample"
	copy etc\ftimes-get.cfg\ftimes-get.cfg.base "$(INSTALL_DIR)\etc\ftimes-get.cfg.sample"
	copy etc\ftimes-map.cfg\ftimes-map.cfg.base "$(INSTALL_DIR)\etc\ftimes-map.cfg.sample"
!IF "$(USE_XMAGIC)" == "Y" || "$(USE_XMAGIC)" == "y"
	copy etc\xmagic\xmagic.base "$(INSTALL_DIR)\etc\xmagic"
!ENDIF
!IF ("$(USE_SSL)" == "Y" || "$(USE_SSL)" == "y") && ("$(USE_STATIC_SSL_LIBS)" == "N" || "$(USE_STATIC_SSL_LIBS)" == "n")
	copy "$(SSL_DLL1)" "$(INSTALL_DIR)\bin"
	copy "$(SSL_DLL2)" "$(INSTALL_DIR)\bin"
!ENDIF
!IF "$(USE_SERVER)" == "Y" || "$(USE_SERVER)" == "y"
	if not exist "$(INSTALL_DIR)\cgi" mkdir "$(INSTALL_DIR)\cgi"
	if not exist "$(INSTALL_DIR)\log" mkdir "$(INSTALL_DIR)\log"
	if not exist "$(INSTALL_DIR)\run" mkdir "$(INSTALL_DIR)\run"
	if not exist "$(INSTALL_DIR)\cgi\cgi-client" mkdir "$(INSTALL_DIR)\cgi\cgi-client"
	copy etc\nph-ftimes.cfg\nph-ftimes.cfg.base" $(INSTALL_DIR)\etc\nph-ftimes.cfg.sample"
	copy tools\nph-ftimes.cgi\nph-ftimes.cgi "$(INSTALL_DIR)\cgi\cgi-client"
!ENDIF

clean:
	if exist "$(OBJECT_DIR)" rd /Q /S "$(OBJECT_DIR)"

clean-all: clean

"$(EXECUTEABLE)": "$(OBJECT_DIR)" $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) $(OBJECTS)
!IF ("$(USE_SSL)" == "Y" || "$(USE_SSL)" == "y") && ("$(USE_STATIC_SSL_LIBS)" == "N" || "$(USE_STATIC_SSL_LIBS)" == "n")
	copy "$(SSL_DLL1)" "$(OBJECT_DIR)"
	copy "$(SSL_DLL2)" "$(OBJECT_DIR)"
!ENDIF

{$(SOURCE_DIR)}.c{$(OBJECT_DIR)}.obj::
	$(COMPILER) $(COMPILER_FLAGS) $<

"$(OBJECT_DIR)":
	if not exist "$(OBJECT_DIR)" mkdir "$(OBJECT_DIR)"

"$(OBJECT_DIR)\analyze.obj": src\analyze.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\cmpmode.obj": src\cmpmode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\compare.obj": src\compare.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\decode.obj": src\decode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\decoder.obj": src\decoder.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\develop.obj": src\develop.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\dig.obj": src\dig.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\digmode.obj": src\digmode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\error.obj": src\error.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\fsinfo.obj": src\fsinfo.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\ftimes.obj": src\ftimes.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\getmode.obj": src\getmode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\http.obj": src\http.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\madmode.obj": src\madmode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\map.obj": src\map.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\mapmode.obj": src\mapmode.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\mask.obj": src\mask.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\md5.obj": src\md5.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\message.obj": src\message.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\options.obj": src\options.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\properties.obj": src\properties.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\sha1.obj": src\sha1.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\sha256.obj": src\sha256.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\socket.obj": src\socket.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\ssl.obj": src\ssl.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\support.obj": src\support.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\time.obj": src\time.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\url.obj": src\url.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\version.obj": src\version.c $(INCLUDES) "$(OBJECT_DIR)"

"$(OBJECT_DIR)\xmagic.obj": src\xmagic.c $(INCLUDES) "$(OBJECT_DIR)"

