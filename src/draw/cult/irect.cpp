#include "draw/common.h"

#include "backing.h"
#include "ipoint.h"
#include "draw/cult/irect.h"
#include "lisp/semantics/cult/calling.h"


using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DIR "draw/irect"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkIPoint> t_skip;
typedef instance<SkIRect> t_skir;



CRAFT_TYPE_DEFINE(SkIRect)
{
	_.add<GraphPropertyName>("craft/draw/IRect");
	_.add<GraphPropertyCppName>("::SkIRect");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkIRect> _this) { return "IRect"; });
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkIRect> _this) { return "IRect"; });
	_.use<PConstructor>().singleton<DefaultConstructor>();
}

void cultlang::draw::make_irect_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();
	LMM(DIR, []() { return t_skir::makeThroughLambda([&](void* s) { *(SkIRect*)s = SkIRect::MakeEmpty(); });  });
	LMM(DIR, [](t_i32 w, t_i32 h) { return t_skir::makeThroughLambda([&](void* s) { *(SkIRect*)s = SkIRect::MakeWH(*w, *h); });  });
	LMM(DIR, [](t_skip xy, t_i32 w, t_i32 h) { return t_skir::makeThroughLambda([&](void* s) { *(SkIRect*)s = SkIRect::MakeXYWH(xy->x(), xy->y(), *w, *h); });  });
	LMM(DIR, [](t_skip x1y1, t_skip x2y2) { return t_skir::makeThroughLambda([&](void* s) { *(SkIRect*)s = SkIRect::MakeLTRB(x1y1->x(), x1y1->y(), x2y2->x(), x2y2->y()); });  });

	LMM(DIR"/inset", [](t_skir x, t_i32 dx, t_i32 dy) { x->inset(*dx, *dy);  });
	LMM(DIR"/intersects", [](t_skir x, t_skir y) { return instance<bool>::make(x->intersect(*x, *y));  });

	LMM(DIR"/left", [](t_skir x) { t_i32::make(x->left());  });
	LMM(DIR"/top", [](t_skir x) { t_i32::make(x->top());  });
	LMM(DIR"/right", [](t_skir x) { t_i32::make(x->right());  });
	LMM(DIR"/bottom", [](t_skir x) { t_i32::make(x->bottom());  });
}