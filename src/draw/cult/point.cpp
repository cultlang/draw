#include "draw/common.h"

#include "backing.h"
#include "draw/cult/point.h"
#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DP "draw/Point"
#define DIP "draw/IPoint"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkPoint> t_skp;
typedef instance<SkIPoint> t_skip;


CRAFT_TYPE_DEFINE(SkPoint)
{
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

CRAFT_TYPE_DEFINE(SkIPoint)
{
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

CRAFT_TYPE_DEFINE(SkMatrix)
{
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

void cultlang::draw::make_point_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	LMM(DP, [](t_f32 x, t_f32 y) { auto res = t_skp::make(); res->set(*x, *y); return res; });
	//LMM(DP, [](instance<glm::uvec2> uvec2) { auto res = t_skp::make(); res->set(uvec2->x, uvec2->y); return res; });
	LMM(DP"/set", [](t_skp p, t_f32 x, t_f32 y) { return p->set(*x, *y); });

	LMM("==", [](t_skp p, t_skp o) { return instance<bool>::make(p->equals(o->fX, o->fY)); });
	LMM("!=", [](t_skp p, t_skp o) { return instance<bool>::make(!p->equals(o->fX, o->fY)); });

	LMM("+", [](t_skp a, t_skp b) { auto r = *a + *b;  auto res = t_skp::make(); res->set(r.fX, r.fY); });
	LMM("*", [](t_skp a, t_f32 b) { auto res = t_skp::make(); a->scale(*b, res.get()); return res; });

	LMM("math/dot", [](t_skp a, t_skp b) { auto res = a->dot(*b); return t_f32::make(res); });
	LMM("math/cross", [](t_skp a, t_skp b) { auto res = a->cross(*b); return t_f32::make(res); });
	LMM("math/distance", [](t_skp a, t_skp b) { auto res = SkPoint::Distance(*a,*b); return t_f32::make(res); });


	LMM(DIP, [](t_i32 x, t_i32 y) { auto res = t_skip::make(); res->set(*x, *y); return res; });
	LMM(DIP"/set", [](t_skip p, t_f32 x, t_f32 y) { return p->set(*x, *y); });

	LMM("==", [](t_skip p, t_skip o) { return instance<bool>::make(p->equals(o->fX, o->fY)); });
	LMM("!=", [](t_skip p, t_skip o) { return instance<bool>::make(!p->equals(o->fX, o->fY)); });

	LMM("+", [](t_skip a, t_skip b) { auto r = *a + *b;  auto res = t_skip::make(); res->set(r.fX, r.fY); });

}