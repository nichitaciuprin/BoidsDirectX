#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <winuser.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
using namespace std;

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "Debug.h"
#include "Math.h"
#include "FileHelper.h"
#include "Time.h"
#include "Subgen.h"
#include "Physics.h"