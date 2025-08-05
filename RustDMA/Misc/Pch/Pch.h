#pragma once
#define NOMINMAX
#include <iostream> 
#include <fstream>
#include <ppltasks.h>
#include <vmmdll.h>
#define DEBUG_INFO
#ifdef DEBUG_INFO
#define LOG(fmt, ...) std::printf(fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) std::wprintf(fmt, ##__VA_ARGS__)
#else
#define LOG
#define LOGW
#endif
#pragma comment(lib, "vmm.lib")
#pragma comment(lib, "leechcore.lib")
#pragma comment(lib, "FTD3XX.lib")
#include "Vector.h"
#include "Memory.h"
#include "Camera.h"
#include "Offsets.h"
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>
#include <atomic>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#define __int128 uint64_t
#include <unordered_set>
#include "Globals.h"
//#include "Transform.h"
#include <future>
#include <random>
#include <json/json.hpp>
#include "Materials.h"