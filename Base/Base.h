#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <memory>
#include <assert.h>
#include <stdint.h>
#include <vector>
#include "Time.h"
#include "Math.h"
#include "SubgenSingleton.h"
#include "Window.h"
#include "D3D.h"
#include "AABB.h"
using namespace std;