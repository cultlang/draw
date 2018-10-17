#pragma once

#include "draw/common.h"
#include "draw/all.h"

namespace cultlang {
namespace draw {
	//template<> instance<SkShader> cultlang::draw::make(instance<SkPoint> a, instance<SkPoint> b, instance<> colors, instance<SkMatrix> mat);

	CULTLANG_DRAW_EXPORTED void make_shader_bindings(craft::types::instance<craft::lisp::Module> m);
}}

CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, SkShader)
