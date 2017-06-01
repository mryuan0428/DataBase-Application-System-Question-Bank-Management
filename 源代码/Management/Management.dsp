# Microsoft Developer Studio Project File - Name="Management" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Management - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Management.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Management.mak" CFG="Management - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Management - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Management - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Management - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Management - Win32 Release"
# Name "Management - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AddandeditDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ado.cpp
# End Source File
# Begin Source File

SOURCE=.\AutoMakeupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowseAllDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BrowsePaperDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DeleteNo.cpp

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EditAnswerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ManageAllDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Management.cpp
# End Source File
# Begin Source File

SOURCE=.\Management.rc
# End Source File
# Begin Source File

SOURCE=.\ManagementDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ManagePaperDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ManagePoolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ManageTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\msword.cpp
# End Source File
# Begin Source File

SOURCE=.\PaperDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonMakeupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\QuestionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveExistDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SavePaperDlg.cpp

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelChapAndDiffDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelChapDlg.cpp

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelDiffDlg.cpp

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelQuesDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AddandeditDlg.h
# End Source File
# Begin Source File

SOURCE=.\ado.h
# End Source File
# Begin Source File

SOURCE=.\AutoMakeupDlg.h
# End Source File
# Begin Source File

SOURCE=.\BrowseAllDlg.h
# End Source File
# Begin Source File

SOURCE=.\BrowsePaperDlg.h
# End Source File
# Begin Source File

SOURCE=.\DeleteNo.h

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EditAnswerDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\ManageAllDlg.h
# End Source File
# Begin Source File

SOURCE=.\Management.h
# End Source File
# Begin Source File

SOURCE=.\ManagementDlg.h
# End Source File
# Begin Source File

SOURCE=.\ManagePaperDlg.h
# End Source File
# Begin Source File

SOURCE=.\ManagePoolDlg.h
# End Source File
# Begin Source File

SOURCE=.\ManageTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\msword.h
# End Source File
# Begin Source File

SOURCE=.\PaperDlg.h
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.h
# End Source File
# Begin Source File

SOURCE=.\PersonMakeupDlg.h
# End Source File
# Begin Source File

SOURCE=.\QuestionDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SaveExistDlg.h
# End Source File
# Begin Source File

SOURCE=.\SavePaperDlg.h

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelChapAndDiffDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelChapDlg.h

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelDiffDlg.h

!IF  "$(CFG)" == "Management - Win32 Release"

!ELSEIF  "$(CFG)" == "Management - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SelQuesDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\ͼƬ\1.BMP"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\2.BMP"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\2007101120568437.ico"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\200789134158139.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\3.BMP"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\ͼƬ\3.BMP"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\4.bmp"
# End Source File
# Begin Source File

SOURCE="E:\�ҵ��ĵ�\My Pictures\����\ͼƬ\5.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\5.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\b.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\back.BMP"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\background.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\bitmap1.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\GY.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\help.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\in.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Management.ico
# End Source File
# Begin Source File

SOURCE=.\res\Management.rc2
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\paper.bmp"
# End Source File
# Begin Source File

SOURCE=".\ͼƬ\ques.bmp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
