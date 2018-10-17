#pragma once

#include "draw/common.h"

namespace cultlang {
namespace draw
{

	CULTLANG_DRAW_EXPORTED void make_rrect_bindings(craft::types::instance<craft::lisp::Module> m);
}}

CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, SkRRect)
