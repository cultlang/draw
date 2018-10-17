#include "draw/common.h"

#include "backing.h"
#include "draw/cult/color.h"
#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkColor> t_skc;


CRAFT_TYPE_DEFINE(cultlang::draw::Color)
{
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<cultlang::draw::Color> _this)
	{
		return fmt::format("A{0}R{1}G{2}B{3}", SkColorGetA(_this->value), SkColorGetR(_this->value), SkColorGetG(_this->value), SkColorGetB(_this->value));
	});
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

void cultlang::draw::make_color_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	LMM("draw/Color/from-rgb", [](t_u8 r, t_u8 g, t_u8 b) { return instance<draw::Color>::make(*r, *g, *b); });
	LMM("draw/Color/from-rgb", [](t_u8 r, t_u8 g, t_u8 b, t_u8 a) { return instance<draw::Color>::make(*r, *g, *b, *a); });

	LMM("draw/Color/from-rgb", [](t_f32 r, t_f32 g, t_f32 b) { return instance<draw::Color>::make(*r, *g, *b); });
	LMM("draw/Color/from-rgb", [](t_f32 r, t_f32 g, t_f32 b, t_f32 a) { return instance<draw::Color>::make(*r, *g, *b, *a); });
}
