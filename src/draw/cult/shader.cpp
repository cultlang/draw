#include "draw/common.h"
#include "draw/all.h"
#include "draw/cult/shader.h"

#include "lisp/semantics/cult/calling.h"
#include "lisp/library/system/prelude.h"

#include "effects/SkGradientShader.h"


using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;
using namespace craft::lisp::library;


#define LMM (semantics->builtin_implementMultiMethod)
#define DS "draw/Shader"

typedef instance<uint32_t> t_u32;
typedef instance<uint8_t> t_u8;
typedef instance<float> t_f32;
typedef instance<bool> t_bool;

typedef instance<SkPaint> t_skp;
typedef instance<SkRect> t_skr;
typedef instance<SkPath> t_skpth;

typedef instance<cultlang::draw::Color> t_cdclr;

CRAFT_TYPE_DEFINE(SkShader)
{
	_.defaults();
}

// template<>
// instance<SkShader> make(instance<SkPoint> a, instance<SkPoint> b, instance<> colors_, instance<SkMatrix> mat)
// {
// 	SkPoint p[2] = { *a, *b };

// 	instance<List> colors = colors_;
// 	int count = (int)*colors->size();
// 	SkColor* clrs = new SkColor[count];
// 	for (int i = 0; i < count; ++i) clrs[i] = colors->at(instance<int64_t>::make(i)).asType<draw::Color>()->value;

// 	auto res = SkGradientShader::MakeLinear(p, clrs, nullptr, count, SkShader::TileMode::kClamp_TileMode, 0, mat ? mat.get() : nullptr).release();
// 	delete clrs;
// 	return instance<SkShader>::makeFromPointerAndMemoryManager(res, +[](void* p) { ((SkShader*)p)->unref(); });
// };

void cultlang::draw::make_shader_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	// // Constructors
	// LMM(DS"/linear-gradient", [](instance<SkPoint> a, instance<SkPoint> b, instance<List> colors)
	// 	{ return make<SkShader>(a, b, (instance<>)colors, instance<SkMatrix>()); });
	// LMM(DS"/linear-gradient", [](instance<SkPoint> a, instance<SkPoint> b, instance<List> colors, instance<SkMatrix> mat)
	// 	{ return make<SkShader>(a, b, (instance<>)colors, mat); });
}
