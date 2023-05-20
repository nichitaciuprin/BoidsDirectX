#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#ifndef UNICODE
#define UNICODE
#endif
#include <windows.h>
#include <memory>
#include <assert.h>
#include <stdint.h>
#include "../Base/Time.h"
#include "../Base/Math.h"
#include "../Base/Math3D.h"
#include "../Base/SubgenSingleton.h"
#include "../Base/Window.h"
#include "../Base/D3D.h"

using namespace std;