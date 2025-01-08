# Microsoft Developer Studio Project File - Name="havoc3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=havoc3d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "havoc3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "havoc3d.mak" CFG="havoc3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "havoc3d - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "havoc3d - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "havoc3d - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /O3 /Qipo /Qparallel /QxW /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\havoc3d.lib"

!ELSEIF  "$(CFG)" == "havoc3d - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\havoc3d_dbg.lib"

!ENDIF 

# Begin Target

# Name "havoc3d - Win32 Release"
# Name "havoc3d - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\check_if_closed.cpp
# End Source File
# Begin Source File

SOURCE=.\color_ids.cpp
# End Source File
# Begin Source File

SOURCE=.\drawslice_gl.cpp
# End Source File
# Begin Source File

SOURCE=.\find_interior.cpp
# End Source File
# Begin Source File

SOURCE=.\find_interior_slice.cpp
# End Source File
# Begin Source File

SOURCE=.\line_distmesh.cpp
# End Source File
# Begin Source File

SOURCE=.\line_distmesh_grad.cpp
# End Source File
# Begin Source File

SOURCE=.\pixel_error.cpp
# End Source File
# Begin Source File

SOURCE=.\pt_distmesh.cpp
# End Source File
# Begin Source File

SOURCE=.\pt_distmesh_grad.cpp
# End Source File
# Begin Source File

SOURCE=.\queries.cpp
# End Source File
# Begin Source File

SOURCE=.\sitecull.cpp
# End Source File
# Begin Source File

SOURCE=.\tri_distmesh.cpp
# End Source File
# Begin Source File

SOURCE=.\tri_distmesh_grad.cpp
# End Source File
# Begin Source File

SOURCE=.\voronoi_slice.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\check_if_closed.hpp
# End Source File
# Begin Source File

SOURCE=.\color_ids.hpp
# End Source File
# Begin Source File

SOURCE=.\drawslice_gl.hpp
# End Source File
# Begin Source File

SOURCE=.\find_interior.hpp
# End Source File
# Begin Source File

SOURCE=.\find_interior_slice.hpp
# End Source File
# Begin Source File

SOURCE=.\grad_utilities.hpp
# End Source File
# Begin Source File

SOURCE=.\line_distmesh.hpp
# End Source File
# Begin Source File

SOURCE=.\line_distmesh_grad.hpp
# End Source File
# Begin Source File

SOURCE=.\pixel_error.hpp
# End Source File
# Begin Source File

SOURCE=.\pt_distmesh.hpp
# End Source File
# Begin Source File

SOURCE=.\pt_distmesh_grad.hpp
# End Source File
# Begin Source File

SOURCE=.\queries.hpp
# End Source File
# Begin Source File

SOURCE=.\sitecull.hpp
# End Source File
# Begin Source File

SOURCE=.\tri_distmesh.hpp
# End Source File
# Begin Source File

SOURCE=.\tri_distmesh_grad.hpp
# End Source File
# Begin Source File

SOURCE=.\voronoi_slice.hpp
# End Source File
# End Group
# End Target
# End Project
