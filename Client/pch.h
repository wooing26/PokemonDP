#pragma once

#include "Types.h"
#include "Enums.h"
#include "Defines.h"
#include "Values.h"
#include "Utils.h"


#include <windows.h>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <functional>
#include <queue>
// using namespace std;

// C++20
#include <format>
#include <filesystem>
namespace fs = std::filesystem;

#define _CRTDEBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

// TransparentBlt
#pragma comment(lib, "msimg32.lib")

#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")