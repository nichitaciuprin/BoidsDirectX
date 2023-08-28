@echo off
SETLOCAL

@REM paths from bat file
set _batdir=%~dp0

set _proj=%_batdir%src\Main
call %_proj%\build.bat

if %errorlevel% neq 0 exit /b %errorlevel%

set _src=%_batdir%src\Main\build
set _target=%_batdir%build
rmdir /S /Q %_target%
mkdir %_target%
xcopy %_src% %_target% /q /E

