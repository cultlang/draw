#include "draw/common.h"

#include "backing.h"
#include "ipoint.h"
#include "draw/cult/rect.h"
#include "draw/cult/rrect.h"
#include "lisp/semantics/cult/calling.h"


using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DRR "draw/rrect"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkPoint> t_skip;
typedef instance<SkRect> t_skr;
typedef instance<SkRRect> t_skrr;



CRAFT_TYPE_DEFINE(SkRRect)
{
	_.add<GraphPropertyName>("craft/draw/RRect");
	_.add<GraphPropertyCppName>("::SkRRect");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkRRect> _this) { return "RRect"; });
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkRRect> _this) { return "RRect"; });
	_.use<PConstructor>().singleton<DefaultConstructor>();
}

void cultlang::draw::make_rrect_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();
	LMM(DRR, []() { return t_skrr::makeThroughLambda([&](void* s) { *(SkRRect*)s = SkRRect::MakeEmpty(); });  });
	LMM(DRR, [](t_skr r) { return t_skrr::makeThroughLambda([&](void* s) { *(SkRRect*)s = SkRRect::MakeOval(*r); });  });
	LMM(DRR, [](t_skr r, t_f32 x, t_f32 y) { return t_skrr::makeThroughLambda([&](void* s) { *(SkRRect*)s = SkRRect::MakeRectXY(*r, *x, *y); });  });

	LMM(DRR"/inset", [](t_skrr x, t_i32 dx, t_i32 dy) { x->inset((float)*dx, (float)*dy);  });
	

}