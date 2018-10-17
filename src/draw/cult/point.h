#pragma once

#include "draw/common.h"

namespace cultlang {
namespace draw 
{

	CULTLANG_DRAW_EXPORTED void make_point_bindings(craft::types::instance<craft::lisp::Module> m);
}}

CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, SkPoint);
CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, SkIPoint);
CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, SkMatrix);
