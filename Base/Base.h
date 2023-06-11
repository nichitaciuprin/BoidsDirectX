#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
using namespace std;
#include <windows.h>
#include <wrl/client.h>
using Microsoft::WRL::ComPtr;
#include <winuser.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "Math.h"
#include "FileHelper.h"
#include "Time.h"
#include "Subgen.h"
#include "Physics.h"
#include "Console.h"