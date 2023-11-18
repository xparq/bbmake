@echo off
rem	This is expected to be called from a (temporary) process context, where
rem	the env. vars won't persist, and won't clash with anything important!

set SZ_APP_NAME=oon

rem !!
rem !! These could crash horrendously, if e.g. the existing value has & in it etc...:
rem !!

if "%SZ_PRJDIR%"=="" set SZ_PRJDIR=%~dp0..
if "%SZ_SFML_LIBROOT%"=="" set SZ_SFML_LIBROOT=%SZ_PRJDIR%/extern/sfml/msvc

set SZ_SRC_SUBDIR=src
set SZ_OUT_SUBDIR=build.out
set SZ_IFC_SUBDIR=ifc
set SZ_RUN_SUBDIR=test
set SZ_ASSET_SUBDIR=asset
set SZ_RELEASE_SUBDIR=release

set SZ_SRC_DIR=%SZ_PRJDIR%/%SZ_SRC_SUBDIR%
set SZ_OUT_DIR=%SZ_PRJDIR%/%SZ_OUT_SUBDIR%
set SZ_RUN_DIR=%SZ_PRJDIR%/%SZ_RUN_SUBDIR%
set SZ_ASSET_DIR=%SZ_PRJDIR%/%SZ_ASSET_SUBDIR%
set SZ_TMP_DIR=%SZ_PRJDIR%/tmp
set SZ_RELEASE_DIR=%SZ_TMP_DIR%/%SZ_RELEASE_SUBDIR%

set COMMIT_HASH_INCLUDE_FILE=%SZ_OUT_DIR%/commit_hash.inc

rem CD to prj root for the rest of the process:
cd "%SZ_PRJDIR%"
if errorlevel 1 (
	echo - ERROR: Failed to enter the project dir ^(%SZ_PRJDIR%^)^!
	exit 1
) else (
	rem Normalize the prj. dir ^(well, stil backslashes, awkwardly differing from the rest...^)
	set SZ_PRJDIR=%CD%
)

if not exist "%SZ_OUT_DIR%" md "%SZ_OUT_DIR%"

set INCLUDE=%SZ_SRC_DIR%;extern/sfw/include;%SZ_SFML_LIBROOT%/include;%SZ_PRJDIR%;%INCLUDE%
set LIB=%SZ_SFML_LIBROOT%/lib;%LIB%
set PATH=%SZ_PRJDIR%/tooling;%SZ_SFML_LIBROOT%/bin;%PATH%;extern/Microsoft.VC143.DebugCRT
:: Lend a hand to w64devkit, so that it can use this same env. setup script:
set C_INCLUDE_PATH=%SZ_SRC_DIR%;extern/sfw/include;%SZ_SFML_LIBROOT%/include;%SZ_PRJDIR%;%C_INCLUDE_PATH%
set CPLUS_INCLUDE_PATH=%SZ_SRC_DIR%;extern/sfw/include;%SZ_SFML_LIBROOT%/include;%SZ_PRJDIR%;%CPLUS_INCLUDE_PATH%
::set C_INCLUDE_PATH=%SZ_SRC_DIR%:extern/sfw/include:%SZ_SFML_LIBROOT%/include:%SZ_PRJDIR%:%C_INCLUDE_PATH%
::set CPLUS_INCLUDE_PATH=%SZ_SRC_DIR%:extern/sfw/include:%SZ_SFML_LIBROOT%/include:%SZ_PRJDIR%:%CPLUS_INCLUDE_PATH%
