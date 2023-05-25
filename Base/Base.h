#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
using namespace std;
#include <windows.h>
#include <string>
#include <memory>
#include <vector>
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
#include "DeviceRecources.h"
#include "Window.h"
#include "CubeRecourse.h"
#include "Renderer.h"
