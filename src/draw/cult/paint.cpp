#include "draw/common.h"
#include "draw/all.h"
#include "draw/cult/paint.h"

#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DP "draw/Paint"

typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkPaint> t_skp;
typedef instance<SkRect> t_skr;
typedef instance<SkPath> t_skpth;
typedef instance<SkShader> t_skshdr;

typedef instance<cultlang::draw::Color> t_cdclr;


CRAFT_TYPE_DEFINE(SkPaint)
{
	_.use<PConstructor>().singleton<DefaultConstructor>();

	_.defaults();
}

void cultlang::draw::make_paint_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	// Constructors
	LMM(DP,[](){ return t_skp::make(); });

	// Reset
	LMM(DP "/reset", [](t_skp p) { p->reset(); });

	// Hash
	LMM(DP "/hash", [](t_skp p) { return t_u32::make(p->getHash()); });

	// Hints
	LMM(DP "/hinting",[](t_skp p) { return t_u32::make(p->getHinting()); });
	LMM(DP "/hinting",[](t_skp p, t_u32 h) {uint32_t target = std::min(int32_t(*h), 3);p->setHinting(SkPaint::Hinting(target));});
	LMM(DP "/hinting/NoHinting", []() {return t_u32::make(SkPaint::kNo_Hinting); });
	LMM(DP "/hinting/NormalHinting	", []() {return t_u32::make(SkPaint::kNormal_Hinting); });
	LMM(DP "/hinting/FullHinting", []() {return t_u32::make(SkPaint::kFull_Hinting); });

	// Flags
#define DPF "draw/paint/Flag"
	LMM(DPF, []() { return t_u32::make(SkPaint::kAntiAlias_Flag); });

	LMM(DPF"/AntiAlias", []() { return t_u32::make(SkPaint::kAntiAlias_Flag); });
	LMM(DPF"/Dither", []() { return t_u32::make(SkPaint::kDither_Flag); });
	LMM(DPF"/FakeBoldText", []() { return t_u32::make(SkPaint::kFakeBoldText_Flag); });
	LMM(DPF"/LinearText", []() { return t_u32::make(SkPaint::kLinearText_Flag); });
	LMM(DPF"/SubpixelText", []() { return t_u32::make(SkPaint::kSubpixelText_Flag); });
	//LMM(DPF"/DevKernText", []() { return t_u32::make(SkPaint::kDevKernText_Flag); });
	LMM(DPF"/LCDRenderText", []() { return t_u32::make(SkPaint::kLCDRenderText_Flag); });
	LMM(DPF"/EmbeddedBitmapText", []() { return t_u32::make(SkPaint::kEmbeddedBitmapText_Flag); });
	LMM(DPF"/AutoHinting", []() { return t_u32::make(SkPaint::kAutoHinting_Flag); });
	LMM(DPF"/VerticalText", []() { return t_u32::make(SkPaint::kVerticalText_Flag); });
	LMM(DPF"/AllFlags", []() { return t_u32::make(SkPaint::kAllFlags); });
#undef DPF

	// Antialias
	LMM(DP "/anti-alias", [](t_skp p) { return t_bool::make(p->isAntiAlias()); });
	LMM(DP "/anti-alias", [](t_skp p, t_bool b) { p->setAntiAlias(*b); });

	// Dither
	LMM(DP "/dither", [](t_skp p) { return t_bool::make(p->isDither()); });
	LMM(DP "/dither", [](t_skp p, t_bool b) { p->setDither(*b); });

	// Subpixel
	LMM(DP "/subpixel", [](t_skp p) { return t_bool::make(p->isSubpixelText()); });
	LMM(DP "/subpixel", [](t_skp p, t_bool b) { p->setSubpixelText(*b); });

	// Subpixel
	LMM(DP "/lcdrender", [](t_skp p) { return t_bool::make(p->isLCDRenderText()); });
	LMM(DP "/lcdrender", [](t_skp p, t_bool b) { p->setLCDRenderText(*b); });

	// Linear Text
	LMM(DP "/lineartext", [](t_skp p) { return t_bool::make(p->isLinearText()); });
	LMM(DP "/lineartext", [](t_skp p, t_bool b) { p->setLinearText(*b); });

	// EmbededBitmapText
	LMM(DP "/embededbitmaptext", [](t_skp p) { return t_bool::make(p->isEmbeddedBitmapText()); });
	LMM(DP "/embededbitmaptext", [](t_skp p, t_bool b) { p->setEmbeddedBitmapText(*b); });

	// Autohinting
	LMM(DP "/autohinting", [](t_skp p) { return t_bool::make(p->isAutohinted()); });
	LMM(DP "/autohinting", [](t_skp p, t_bool b) { p->setAutohinted(*b); });

	// Vertical
	LMM(DP "/verticaltext", [](t_skp p) { return t_bool::make(p->isVerticalText()); });
	LMM(DP "/verticaltext", [](t_skp p, t_bool b) { p->setVerticalText(*b); });

	// FakeFOld
	LMM(DP "/fakebold", [](t_skp p) { return t_bool::make(p->isFakeBoldText()); });
	LMM(DP "/fakebold", [](t_skp p, t_bool b) { p->setFakeBoldText(*b); });

	// DevKern
	LMM(DP "/devkern", [](t_skp p) { t_bool::make(p->isDevKernText()); });
	LMM(DP "/devkern", [](t_skp p, t_bool b) { p->setDevKernText(*b); });

	// Filter Quality
#define DPFQ "draw/paint/FilterQuality"
	LMM(DPFQ, [](t_skp p) { return t_u32::make(p->getFilterQuality()); });
	LMM(DPFQ, [](t_skp p, t_u32 q) { p->setFilterQuality(SkFilterQuality(*q)); });

	LMM(DPFQ"/None", []() { return t_u32::make(SkFilterQuality::kNone_SkFilterQuality); });
	LMM(DPFQ"/Low", []() { return t_u32::make(SkFilterQuality::kLow_SkFilterQuality); });
	LMM(DPFQ"/Medium", []() { return t_u32::make(SkFilterQuality::kMedium_SkFilterQuality); });
	LMM(DPFQ"/High", []() { return t_u32::make(SkFilterQuality::kHigh_SkFilterQuality); });
#undef DPFQ

	// Colors
	LMM(DP "/color", [](t_skp p) { return t_u32::make(p->getColor()); });
	LMM(DP "/color", [](t_skp p, t_cdclr c) { p->setColor(c->value); });

	//LMM(DP "/shader", [](t_skp p) { return p->getShader(); }); // TODO: repackage...
	LMM(DP "/shader", [](t_skp p, t_skshdr c) { p->setShader((sk_sp<SkShader>)c.get()); });

	//Style
	LMM(DP "/style", [](t_skp p) { return t_u32::make(p->getStyle()); });
	LMM(DP "/style", [](t_skp p, t_u32 c) { p->setStyle(SkPaint::Style(*c)); });
	LMM(DP "/Style/Stroke", []() { return t_u32::make(SkPaint::Style::kStroke_Style); });
	LMM(DP "/Style/Dill", []() { return t_u32::make(SkPaint::Style::kFill_Style); });
	LMM(DP "/Style/StrokeAndFill", []() { return t_u32::make(SkPaint::Style::kStrokeAndFill_Style); });

	// Stroke Functions
	LMM(DP "/stroke-width", [](t_skp p) { return t_f32::make(p->getStrokeWidth()); });
	LMM(DP "/stroke-width", [](t_skp p, t_f32 c) { p->setStrokeWidth(*c); });
	
	LMM(DP "/stroke-miter", [](t_skp p) { return t_f32::make(p->getStrokeMiter()); });
	LMM(DP "/stroke-miter", [](t_skp p, t_f32 c) { p->setStrokeMiter(*c); });

	LMM(DP "/stroke-cap", [](t_skp p) { return t_u32::make(p->getStrokeCap()); });
	LMM(DP "/stroke-cap", [](t_skp p, t_u32 c) { p->setStrokeCap(SkPaint::Cap(*c)); });
	LMM(DP "/Cap/Butt", []() { return t_u32::make(SkPaint::Cap::kButt_Cap); });
	LMM(DP "/Cap/Round", []() { return t_u32::make(SkPaint::Cap::kRound_Cap); });
	LMM(DP "/Cap/Square", []() { return t_u32::make(SkPaint::Cap::kSquare_Cap); });

	LMM(DP "/stroke/join", [](t_skp p) { return t_u32::make(p->getStrokeJoin()); });
	LMM(DP "/stroke/join", [](t_skp p, t_u32 c) { p->setStrokeJoin(SkPaint::Join(*c)); });
	LMM(DP "/Join/Miter", []() { return t_u32::make(SkPaint::Join::kMiter_Join); });
	LMM(DP "/Join/Round", []() { return t_u32::make(SkPaint::Join::kRound_Join); });
	LMM(DP "/Join/Bevel", []() { return t_u32::make(SkPaint::Join::kBevel_Join); });

	// Need Paths Stopped https://skia.org/user/api/SkPaint_Reference#Fill_Path
	LMM(DP "/fillpath", [](t_skp p, t_skpth src, t_skr cull, t_f32 scale) { auto res = t_skpth::make(); p->getFillPath(*src, res.get(), cull.get(), *scale); return res; });
}