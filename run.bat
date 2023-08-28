@echo off
SETLOCAL

@REM paths from bat file
set _batdir=%~dp0

call %_batdir%build\BoidsDirectX.exe

