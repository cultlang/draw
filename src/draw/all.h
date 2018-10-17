#pragma once

#include "draw/common.h"

namespace cultlang {
namespace draw 
{
	
	CULTLANG_DRAW_EXPORTED extern craft::lisp::BuiltinModuleDescription DrawModule;
	CULTLANG_DRAW_EXPORTED void make_draw_bindings(craft::types::instance<craft::lisp::Module> m);
}}

#include "draw/cult/backing.h"
#include "draw/cult/color.h"
#include "draw/cult/rect.h"
#include "draw/cult/rrect.h"
#include "draw/cult/irect.h"
#include "draw/cult/path.h"
#include "draw/cult/point.h"
#include "draw/cult/shader.h"
#include "draw/cult/paint.h"
#include "draw/cult/canvas.h"
