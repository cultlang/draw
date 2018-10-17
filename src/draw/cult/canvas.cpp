#include "draw/common.h"
#include "draw/all.h"
#include "draw/cult/canvas.h"

#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DC "draw/Canvas"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;
typedef instance<std::string> t_str;

typedef instance<SkCanvas> t_skc;
typedef instance<SkPaint> t_skpnt;
typedef instance<SkPoint> t_skp;
typedef instance<SkRect> t_skr;
typedef instance<SkIRect> t_skir;
typedef instance<SkRRect> t_skrr;
typedef instance<SkPath> t_skpth;
typedef instance<SkImage> t_skimg;

typedef instance<draw::Color> t_cdclr;

CRAFT_TYPE_DEFINE(SkCanvas)
{
	_.add<GraphPropertyName>("cult/SkCanvas");
	_.add<GraphPropertyCppName>("::SkCanvas");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkCanvas> _this) {
		return "SkCanvas";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkCanvas> _this) {
		return "SkCanvas";
	});
}

// template<> instance<SkCanvas> cultlang::draw::make(instance<SkSurface> back)
// {
// 	return instance<SkCanvas>::makeFromPointerAndMemoryManager(back->getCanvas(), back.asInternalPointer());
// }

void cultlang::draw::make_canvas_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	LMM(DC, [](instance<SkSurface> back) {
		auto canvas = back->getCanvas();
		auto res = instance<SkCanvas>::makeFromPointerAndMemoryManager(canvas, back.asInternalPointer());
		auto tmp = res.get();
		return res;
	});

	LMM(DC"/flush", [](t_skc c) {c->flush(); });
	LMM(DC"/restore", [](t_skc c) { c->restore(); });
	LMM(DC"/restore", [](t_skc c, t_i32 i) {c->restoreToCount(*i); });
	LMM(DC"/save", [](t_skc c) {return t_i32::make(c->save()); });
	LMM(DC"/save/layer", [](t_skc c, t_skr bounds) {return t_i32::make(c->saveLayer(*bounds, nullptr)); });
	LMM(DC"/save/layer", [](t_skc c, t_skr bounds, t_skpnt p) {return t_i32::make(c->saveLayer(*bounds, p.get())); });

	LMM(DC"/clear", [](t_skc c, t_cdclr col) {return c->clear(col->value);});
	

	LMM(DC"/clip/path", [](t_skc c, t_skpth p, t_bool aa) { return c->clipPath(*p, *aa);});
	LMM(DC"/clip/rect", [](t_skc c, t_skr p, t_bool aa) { return c->clipRect(*p, *aa); });

	LMM(DC"/discard", [](t_skc c) {return c->discard(); });

	LMM(DC"/BlendMode/src", []() { return t_u32::make(uint32_t(SkBlendMode::kSrc)); });
	LMM(DC"/BlendMode/srcover", []() { return t_u32::make(uint32_t(SkBlendMode::kSrcOver)); });
	LMM(DC"/BlendMode/plus", []() { return t_u32::make(uint32_t(SkBlendMode::kPlus)); });

	LMM(DC"/draw-color", [](t_skc c, t_cdclr col, t_u32 blend) { c->drawColor(col->value, SkBlendMode(*blend)); });

	LMM(DC"/draw-arc", [](t_skc c, t_skr o, t_f32 saA, t_f32 swA, t_bool cent, t_skpnt p) { c->drawArc(*o, *saA, *swA, *cent, *p); });

	LMM(DC"/draw-circle", [](t_skc c, t_f32 x, t_f32 y, t_f32 radius, t_skpnt p) { c->drawCircle(*x, *y, *radius, *p); });

	LMM(DC"/draw-image", [](t_skc c, t_skimg img, t_f32 left, t_f32 top) { c->drawImage(img.get(), *left, *top); });
	LMM(DC"/draw-image", [](t_skc c, t_skimg img, t_f32 left, t_f32 top, t_skpnt p) { c->drawImage(img.get(), *left, *top, p.get()); });
	LMM(DC"/draw-image", [](t_skc c, t_skimg img, t_skr src, t_skr dest, t_skpnt p) { c->drawImageRect(img.get(), *src, *dest, p.get()); });

	LMM(DC"/draw-line", [](t_skc c, t_f32 x0, t_f32 y0, t_f32 x1, t_f32 y1, t_skpnt p) { c->drawLine(*x0, *y0, *x1, *y1, *p); });
	LMM(DC"/draw-line", [](t_skc c, t_skp xy0, t_skp xy1, t_skpnt p) { c->drawLine(*xy0, *xy1, *p); });

	LMM(DC"/draw-oval", [](t_skc c, t_skr rect, t_skpnt p) { c->drawOval(*rect, *p); });

	LMM(DC"/draw-paint", [](t_skc c, t_skpnt p) { c->drawPaint(*p); });

	LMM(DC"/draw-path", [](t_skc c, t_skpth path, t_skpnt p) { c->drawPath(*path, *p); });

	LMM(DC"/draw-point", [](t_skc c, t_f32 x0, t_f32 y0, t_skpnt p) { c->drawPoint(*x0,*y0, *p); });
	LMM(DC"/draw-point", [](t_skc c, t_skp xy0, t_skpnt p) { c->drawPoint(*xy0, *p); });

	LMM(DC"/draw-rect", [](t_skc c, t_skrr outer, t_skrr inner, t_skpnt p) { c->drawDRRect(*outer, *inner, *p); });
	LMM(DC"/draw-rect", [](t_skc c, t_skir rect, t_skpnt p) { c->drawIRect(*rect, *p); });
	LMM(DC"/draw-rect", [](t_skc c, t_skr rect, t_skpnt p) { c->drawRect(*rect, *p); });
	LMM(DC"/draw-roundrect", [](t_skc c, t_skr rect, t_f32 rx, t_f32 ry, t_skpnt p) { c->drawRoundRect(*rect, *rx, *ry, *p); });

	LMM(DC"/draw-string", [](t_skc c, t_str data, t_f32 x, t_f32 y, t_skpnt p) { c->drawString(data->c_str(), *x, *y, *p); });
}