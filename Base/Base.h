#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
using namespace std;
#include <windows.h>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
wstring GetCurentDirectoryPath()
{
    wchar_t buffer[MAX_PATH] = {};
    GetCurrentDirectory(MAX_PATH, (LPWSTR)buffer);
    return wstring(buffer,sizeof(buffer));
}
wstring GetExeFilePath()
{
    wchar_t buffer[MAX_PATH] = {};
    GetModuleFileName(NULL, (LPWSTR)buffer, MAX_PATH);
    return wstring(buffer,sizeof(buffer));
}
void ShowMessageBox(LPCSTR lpText)
{
    MessageBoxA(nullptr, lpText, nullptr, MB_OK);
}
bool FileExists(LPCWSTR file)
{
    return GetFileAttributes(file) != INVALID_FILE_ATTRIBUTES;
}
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include "Time.h"
#include "Math.h"
#include "Subgen.h"
#include "Physics.h"
#include <winuser.h>
#include <stdlib.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "DeviceRecources.h"
#include "Window.h"
#include "CubeRecourse.h"
#include "Renderer.h"
