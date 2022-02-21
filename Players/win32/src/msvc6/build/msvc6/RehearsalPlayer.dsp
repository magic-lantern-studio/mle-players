# Microsoft Developer Studio Project File - Name="RehearsalPlayer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RehearsalPlayer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RehearsalPlayer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RehearsalPlayer.mak" CFG="RehearsalPlayer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RehearsalPlayer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "RehearsalPlayer - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE "RehearsalPlayer - Win32 Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "RehearsalPlayer - Win32 Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE "RehearsalPlayer - Win32 Unicode Release MinSize" (based on "Win32 (x86) Application")
!MESSAGE "RehearsalPlayer - Win32 Unicode Release MinDependency" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RehearsalPlayer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DEBUG" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mleatkd.lib ivrolesd.lib Mle2dSetd.lib Mle3dSetd.lib DWPd.lib MleIvStaged.lib mlertd.lib mlmathd.lib coin2d.lib sowin1d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\Debug
TargetPath=.\Debug\RehearsalPlayer.exe
InputPath=.\Debug\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RehearsalPlayer - Win32 Unicode Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DebugU"
# PROP BASE Intermediate_Dir "DebugU"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugU"
# PROP Intermediate_Dir "DebugU"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DEBUG" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D ML_MATH_DEBUG=1 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 mleatkd.lib ivrolesd.lib Mle2dSetd.lib Mle3dSetd.lib DWPd.lib MleIvStaged.lib mlertd.lib mlmathd.lib coin2d.lib sowin1d.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\DebugU
TargetPath=.\DebugU\RehearsalPlayer.exe
InputPath=.\DebugU\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RehearsalPlayer - Win32 Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinSize"
# PROP BASE Intermediate_Dir "ReleaseMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinSize"
# PROP Intermediate_Dir "ReleaseMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mleatk.lib ivroles.lib Mle2dSet.lib Mle3dSet.lib DWP.lib MleIvStage.lib mlert.lib mlmath.lib coin2.lib sowin1.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinSize
TargetPath=.\ReleaseMinSize\RehearsalPlayer.exe
InputPath=.\ReleaseMinSize\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RehearsalPlayer - Win32 Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseMinDependency"
# PROP BASE Intermediate_Dir "ReleaseMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseMinDependency"
# PROP Intermediate_Dir "ReleaseMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mleatk.lib ivroles.lib Mle2dSet.lib Mle3dSet.lib DWP.lib MleIvStage.lib mlert.lib mlmath.lib coin2.lib sowin1.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseMinDependency
TargetPath=.\ReleaseMinDependency\RehearsalPlayer.exe
InputPath=.\ReleaseMinDependency\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RehearsalPlayer - Win32 Unicode Release MinSize"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinSize"
# PROP BASE Intermediate_Dir "ReleaseUMinSize"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinSize"
# PROP Intermediate_Dir "ReleaseUMinSize"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_DLL" /D "_ATL_MIN_CRT" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mleatk.lib ivroles.lib Mle2dSet.lib Mle3dSet.lib DWP.lib MleIvStage.lib mlert.lib mlmath.lib coin2.lib sowin1.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinSize
TargetPath=.\ReleaseUMinSize\RehearsalPlayer.exe
InputPath=.\ReleaseUMinSize\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RehearsalPlayer - Win32 Unicode Release MinDependency"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseUMinDependency"
# PROP BASE Intermediate_Dir "ReleaseUMinDependency"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseUMinDependency"
# PROP Intermediate_Dir "ReleaseUMinDependency"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "$(MLE_HOME)/include" /I "$(MLE_HOME)/tools/3rdparty/WTL/include" /I "$(COINDIR)/include" /D "MLE_REHEARSAL" /D "MLE_DLL" /D "COIN_DLL" /D "SOWIN_DLL" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "_ATL_STATIC_REGISTRY" /D "_ATL_MIN_CRT" /D ML_MATH_DEBUG=0 /D ML_FIXED_POINT=0 /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 mleatk.lib ivroles.lib Mle2dSet.lib Mle3dSet.lib DWP.lib MleIvStage.lib mlert.lib mlmath.lib coin2.lib sowin1.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /libpath:"$(MLE_HOME)/lib/rehearsal" /libpath:"$(MLE_HOME)/lib/tools" /libpath:"$(COINDIR)/lib"
# Begin Custom Build - Performing registration
OutDir=.\ReleaseUMinDependency
TargetPath=.\ReleaseUMinDependency\RehearsalPlayer.exe
InputPath=.\ReleaseUMinDependency\RehearsalPlayer.exe
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if "%OS%"=="" goto NOTNT 
	if not "%OS%"=="Windows_NT" goto NOTNT 
	"$(TargetPath)" /RegServer 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	echo Server registration done! 
	goto end 
	:NOTNT 
	echo Warning : Cannot register Unicode EXE on Windows 95 
	:end 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "RehearsalPlayer - Win32 Debug"
# Name "RehearsalPlayer - Win32 Unicode Debug"
# Name "RehearsalPlayer - Win32 Release MinSize"
# Name "RehearsalPlayer - Win32 Release MinDependency"
# Name "RehearsalPlayer - Win32 Unicode Release MinSize"
# Name "RehearsalPlayer - Win32 Unicode Release MinDependency"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\RehearsalPlayer\AuStage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\PlayerWindow.cxx
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\RehearsalPlayer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\RehearsalPlayer.idl
# ADD MTL /tlb "..\..\RehearsalPlayer\RehearsalPlayer.tlb" /h "RehearsalPlayer.h" /iid "RehearsalPlayer_i.c" /Oicf
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\RehearsalPlayer.rc
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\title.cxx
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\RehearsalPlayer\AuStage.h
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\BaseWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\PlayerWindow.h
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\RehearsalPlayer\austage.bmp
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\AuStage.rgs
# End Source File
# Begin Source File

SOURCE=..\..\RehearsalPlayer\RehearsalPlayer.rgs
# End Source File
# End Group
# End Target
# End Project
