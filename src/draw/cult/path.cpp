#include "draw/common.h"

#include "backing.h"
#include "path.h"
#include "draw/cult/rect.h"
#include "draw/cult/point.h"
#include "lisp/semantics/cult/calling.h"
#include "lisp/library/system/prelude.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DP "draw/path"

typedef instance<uint32_t> t_i32;
typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<craft::lisp::library::List> t_list;

typedef instance<SkPoint> t_skp;
typedef instance<SkRect> t_skr;
typedef instance<SkPath> t_skpth;



CRAFT_TYPE_DEFINE(SkPath)
{
	_.add<GraphPropertyName>("craft/draw/Path");
	_.add<GraphPropertyCppName>("::SkPath");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkPath> _this) { return "Path"; });
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkPath> _this) { return "Path"; });
	_.use<PConstructor>().singleton<DefaultConstructor>();
}

void cultlang::draw::make_path_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();
	
	LMM(DP, []() { return t_skpth::make(); });

	LMM(DP"/addArc", [](t_skpth s, t_skr o, t_f32 saA, t_f32 swA) { s->addArc(*o, *saA, *swA); });
	
	LMM(DP"/addCircle", [](t_skpth s, t_f32 x, t_f32 y, t_f32 radius) { s->addCircle(*x, *y, *radius); });
	LMM(DP"/addCircle", [](t_skpth s, t_f32 x, t_f32 y, t_f32 radius, t_bool cw) { s->addCircle(*x, *y, *radius, (*cw) ? SkPath::kCW_Direction : SkPath::kCCW_Direction); });

	LMM(DP"/addOval", [](t_skpth s, t_skr r) { s->addOval(*r); });
	LMM(DP"/addOval", [](t_skpth s, t_skr r, t_bool cw) { s->addOval(*r, (*cw) ? SkPath::kCW_Direction : SkPath::kCCW_Direction); });
	
	LMM(DP"/addPath", [](t_skpth s, t_skpth o, t_f32 x, t_f32 y) { s->addPath(*s, *x, *y); });
	
	LMM(DP"/addOval", [](t_skpth s, t_f32 x, t_f32 y, t_bool ext) { s->addPath(*s, *x, *y, (*ext) ? SkPath::kExtend_AddPathMode : SkPath::kAppend_AddPathMode); });
	
	LMM(DP"/addPoly", [](t_skpth s, t_list points, t_bool close) { 
		std::vector<SkPoint> p;
		for (auto it : points->data())
		{
			if (!it.isType<SkPoint>()) throw stdext::exception("List must be homgononus over type SkPoint");
			p.push_back(*it.asType<SkPoint>().get());
		}
		s->addPoly(p.data(), int32_t(p.size()), *close);
	});

	//TODO implement RoundRect LMM(DP"/addRRect", [](t_skpth s, t_list points, t_bool close) { 
	
	LMM(DP"/addRect", [](t_skpth s, t_skr r) { s->addRect(*r); });
	LMM(DP"/addRect", [](t_skpth s, t_skr r, t_bool cw) { s->addRect(*r, (*cw) ? SkPath::kCW_Direction : SkPath::kCCW_Direction); });

	LMM(DP"/arcTo", [](t_skpth s, t_skr o, t_f32 saA, t_f32 swA) { s->arcTo(*o, *saA, *swA, false); });
	LMM(DP"/arcTo", [](t_skpth s, t_skr o, t_f32 saA, t_f32 swA, t_bool fmT) { s->arcTo(*o, *saA, *swA, *fmT); });

	LMM(DP"/close", [](t_skpth s) { s->close(); });

	LMM(DP"/computeTightBounds", [](t_skpth s) { return t_skr::makeThroughLambda([&](void* p) { *(SkRect*)p = s->computeTightBounds(); }); });
	
	LMM(DP"/conicTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2, t_f32 w) { s->conicTo(*x1, *y1, *x2, *y2, *w); });
	LMM(DP"/conicTo", [](t_skpth s, t_skp xy1, t_skp xy2, t_f32 w) { s->conicTo(*xy1, *xy2, *w); });

	LMM(DP"/conservativelyContainsRect", [](t_skpth s, t_skr r) { return t_bool::make(s->conservativelyContainsRect(*r)); });

	LMM(DP"/contains", [](t_skpth s, t_f32 x, t_f32 y) { return t_bool::make(s->contains(*x, *y)); });

	LMM(DP"/countPoints", [](t_skpth s) { return t_i32::make(s->countPoints()); });

	LMM(DP"/countVerbs", [](t_skpth s) { return t_i32::make(s->countVerbs()); });

	LMM(DP"/cubicTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2, t_f32 x3, t_f32 y3) { s->cubicTo(*x1, *y1, *x2, *y2, *x3, *y3); });
	LMM(DP"/cubicTo", [](t_skpth s, t_skp xy1, t_skp xy2, t_skp xy3 ) { s->cubicTo(*xy2, *xy2, *xy3); });

	LMM(DP"/bounds", [](t_skpth s) { return t_skr::makeThroughLambda([&](void* p) { *(SkRect*)p = s->getBounds(); }); });


	// Convexity
	LMM(DP"/convex", [](t_skpth s) { return t_bool::make(s->isConvex()); });
	LMM(DP"/convexity", [](t_skpth s) { return t_u32::make(s->getConvexity()); });
	LMM(DP"/convexity/kUnknown_Convexity", []() { return t_u32::make(SkPath::kUnknown_Convexity); });
	LMM(DP"/convexity/kConvex_Convexity", []() { return t_u32::make(SkPath::kConvex_Convexity); });
	LMM(DP"/convexity/kConvex_Convexity", []() { return t_u32::make(SkPath::kConcave_Convexity); });
	
	// FillType
	LMM(DP"/filltype", [](t_skpth s) { return t_u32::make(s->getFillType()); });
	LMM(DP"/filltype", [](t_skpth s, t_u32 ft) { s->setFillType(SkPath::FillType(*ft)); });
	LMM(DP"/filltype/kWinding_FillType", []() { return t_u32::make(SkPath::kWinding_FillType); });
	LMM(DP"/filltype/kEvenOdd_FillType", []() { return t_u32::make(SkPath::kEvenOdd_FillType); });
	LMM(DP"/filltype/kInverseWinding_FillType", []() { return t_u32::make(SkPath::kInverseWinding_FillType); });
	LMM(DP"/filltype/kInverseEvenOdd_FillType", []() { return t_u32::make(SkPath::kInverseEvenOdd_FillType); });

	LMM(DP"/filltype/inverse", [](t_skpth s) { return t_bool::make(s->isInverseFillType()); });

	LMM(DP"/generationID", [](t_skpth s) { t_u32::make(s->getGenerationID()); });

	LMM(DP"/lastPoint", [](t_skpth s) { auto res = t_skp::make(); s->getLastPt(res.get()); return res; });
	LMM(DP"/lastPoint", [](t_skpth s, t_f32 x, t_f32 y) { s->setLastPt(*x, *y); });

	LMM(DP"/point", [](t_skpth s, t_i32 i) { return t_skp::make(s->getPoint(*i)); });
	//TODO GetPoints

	LMM(DP"/segmentMasks", [](t_skpth s) { return t_u32::make(s->getSegmentMasks()); });

	LMM(DP"/interpolate", [](t_skpth s, t_skpth o, t_f32 weight) { auto res = t_skpth::make(); s->interpolate(*o, *weight, res.get());  return res; });
	LMM(DP"/interpolatable", [](t_skpth s, t_skpth o) { return t_bool::make(s->isInterpolatable(*o)); });

	LMM(DP"/empty", [](t_skpth s) { return t_bool::make(s->isEmpty()); });

	LMM(DP"/finite", [](t_skpth s) { return t_bool::make(s->isFinite()); });

	
	LMM(DP"/volitile", [](t_skpth s) { return t_bool::make(s->isVolatile()); });
	LMM(DP"/volitile", [](t_skpth s, t_bool b) {s->setIsVolatile(*b); });

	LMM(DP"/lastcontourclosed", [](t_skpth s) {return t_bool::make(s->isLastContourClosed()); });

	LMM(DP"/lineto", [](t_skpth s, t_f32 x, t_f32 y) {s->lineTo(*x, *y); });
	LMM(DP"/lineto", [](t_skpth s, t_skp p) {s->lineTo(*p); });

	LMM(DP"/moveto", [](t_skpth s, t_f32 x, t_f32 y) {s->moveTo(*x, *y); });
	LMM(DP"/moveto", [](t_skpth s, t_skp p) {s->moveTo(*p); });

	LMM(DP"/offset", [](t_skpth s, t_f32 x, t_f32 y) {s->offset(*x, *y); });

	LMM(DP"/quadTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2) { s->quadTo(*x1, *y1, *x2, *y2); });
	LMM(DP"/quadTo", [](t_skpth s, t_skp xy1, t_skp xy2) { s->quadTo(*xy1, *xy2); });

	/*LMM(DP"/rarcTo", [](t_skpth s, t_f32 rx, t_f32 ry, t_f32 saR, t_f32 swA) { s->rarcTo(*o, *saA, *swA, false); });
	/LMM(DP"/rarcTo", [](t_skpth s, t_skr o, t_f32 saA, t_f32 swA, t_bool fmT) { s->rarcTo(*o, *saA, *swA, *fmT); });*/

	LMM(DP"/rconicTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2, t_f32 w) { s->rConicTo(*x1, *y1, *x2, *y2, *w); });

	LMM(DP"/rcubicTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2, t_f32 x3, t_f32 y3) { s->rCubicTo(*x1, *y1, *x2, *y2, *x3, *y3); });

	LMM(DP"/rlineTo", [](t_skpth s, t_f32 x, t_f32 y) {s->rLineTo(*x, *y); });

	LMM(DP"/rmoveTo", [](t_skpth s, t_f32 x, t_f32 y) {s->rMoveTo(*x, *y); });

	LMM(DP"/rQuadTo", [](t_skpth s, t_f32 x1, t_f32 y1, t_f32 x2, t_f32 y2) { s->rQuadTo(*x1, *y1, *x2, *y2); });
}