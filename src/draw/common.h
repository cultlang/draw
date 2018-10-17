#pragma once

#include "defines.h"


// C
#include <cmath>

// C++
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <stack>
#include <queue>
#include <set>
#include <chrono>
#include <memory>
#include <type_traits>
#include <functional>

//
// Vendor
//
// Vendor
#pragma warning( disable : 4635)  
#include "glm/glm.hpp"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "gl/GrGLInterface.h"
#include "GrBackendSurface.h"

#include "SkCanvas.h"
#include "SkSurface.h"
#include "SkPath.h"
#include "SkPaint.h"
#include "GrContext.h"


#pragma warning( default : 4635)  


// Deps
#include "util/all.h"
#include "types/core.h"
#include "lisp/lisp.h"
