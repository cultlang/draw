#pragma once

#include "draw/common.h"
#include "draw/all.h"

namespace cultlang {
namespace draw
{
	// TODO move this to/use mmds
	struct Color
	{
		SkColor value;

		CULTLANG_DRAW_EXPORTED Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xFF)
			: value((a << 24) + (r << 16) + (g << 8) + (b))
		{ }
		CULTLANG_DRAW_EXPORTED Color(float r, float g, float b, float a = 1.0)
			: Color(static_cast<uint8_t>(r * 255),
				static_cast<uint8_t>(g * 255),
				static_cast<uint8_t>(b * 255),
				static_cast<uint8_t>(a * 255))
		{ }
	};

	CULTLANG_DRAW_EXPORTED void make_color_bindings(craft::types::instance<craft::lisp::Module> m);
}}

CRAFT_TYPE_DECLARE(CULTLANG_DRAW_EXPORTED, cultlang::draw::Color);
