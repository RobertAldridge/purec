# Microsoft Developer Studio Project File - Name="swift" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=swift - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "swift.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "swift.mak" CFG="swift - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "swift - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "swift - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "swift - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I ".\include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "LOOKUP_TABLE_5_625" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "swift - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
LINK32=link.exe -lib
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I ".\include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "LOOKUP_TABLE_5_625" /YX /FD /GZ /c /Tp
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "swift - Win32 Release"
# Name "swift - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\fileio.cpp
# End Source File
# Begin Source File

SOURCE=.\src\lut.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mesh_hier.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mesh_utils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\object.cpp
# End Source File
# Begin Source File

SOURCE=.\src\pair.cpp
# End Source File
# Begin Source File

SOURCE=.\src\scene.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\SWIFT.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_array.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_boxnode.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_common.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_config.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_fileio.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_linalg.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_lut.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_mesh.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_mesh_utils.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_object.h
# End Source File
# Begin Source File

SOURCE=.\include\SWIFT_pair.h
# End Source File
# End Group
# End Target
# End Project
