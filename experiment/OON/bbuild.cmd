::
:: Build with BusyBox-w32 & MSVC
::
@echo off
call %~dp0tooling/_setenv.cmd
:! Can't use _setenv.sh from a CMD script, even if the rest is basically
:! all SH: those vars can't propagate to Windows, let alone back to SH again. :)

::!! wtime GETS CONFUST BY THE QUOTED PARAM! :-o : %~dp0tooling/diag/wtime.exe 
busybox sh -c "export SZ_PRJDIR=. && . tooling/_setenv.sh && busybox make -f bbMakefile.msvc %*"

:: The original (BB/sh-scripted) build process with auto-rebuild:
::busybox sh %~dp0tooling/build/_auto-rebuild.sh %*
