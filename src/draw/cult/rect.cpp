#include "draw/common.h"

#include "backing.h"
#include "point.h"
#include "draw/cult/rect.h"
#include "lisp/semantics/cult/calling.h"


using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DR "draw/rect"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkPoint> t_skp;
typedef instance<SkRect> t_skr;
typedef instance<SkMatrix> t_skmat;



CRAFT_TYPE_DEFINE(SkRect)
{
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

void cultlang::draw::make_rect_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();
	LMM(DR, []() { return t_skr::makeThroughLambda([&](void* s) { *(SkRect*)s = SkRect::MakeEmpty(); });  });
	LMM(DR, [](t_f32 w, t_f32 h) { return t_skr::makeThroughLambda([&](void* s) { *(SkRect*)s = SkRect::MakeWH(*w, *h); });  });
	LMM(DR, [](t_skp xy, t_f32 w, t_f32 h) { return t_skr::makeThroughLambda([&](void* s) { *(SkRect*)s = SkRect::MakeXYWH(xy->x(), xy->y(), *w, *h); });  });
	LMM(DR, [](t_skp x1y1, t_skp x2y2) { return t_skr::makeThroughLambda([&](void* s) { *(SkRect*)s = SkRect::MakeLTRB(x1y1->x(), x1y1->y(), x2y2->x(), x2y2->y()); });  });

	LMM(DR"/inset", [](t_skr x, t_f32 dx, t_f32 dy) { auto ret = t_skr::make(*x); ret->inset(*dx, *dy); return ret;  });
	LMM(DR"/intersects", [](t_skr x, t_skr y) { return instance<bool>::make(x->intersect(*x, *y)); });

	LMM(DR"/left", [](t_skr x) { t_f32::make(x->left());  });
	LMM(DR"/top", [](t_skr x) { t_f32::make(x->top());  });
	LMM(DR"/right", [](t_skr x) { t_f32::make(x->right());  });
	LMM(DR"/bottom", [](t_skr x) { t_f32::make(x->bottom());  });

	LMM("math/to-matrix", [](t_skr r) { auto res = t_skmat::make(); res->setScaleTranslate(r->width(), r->height(), r->left(), r->top()); return res; });
}

