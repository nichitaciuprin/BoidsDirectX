#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
using namespace std;
#include <windows.h>
#include <memory>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <vector>
#include "Time.h"
#include "Math.h"
#include "SubgenSingleton.h"
#include "AABB.h"
#include "D3D.h"
#include "Window.h"
#include "CubeRecourse.h"
#include "Renderer.h"