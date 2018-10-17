#include "draw/common.h"

#include "draw/cult/backing.h"
#include "lisp/semantics/cult/calling.h"

using namespace craft;
using namespace cultlang;
using namespace craft::types;
using namespace craft::lisp;

#define LMM (semantics->builtin_implementMultiMethod)
#define DP "draw"


/// CAN I GET AWAY WITH NEVER ACTUALLY WRITING OPENGL BINDINGS
#ifndef GL_RGBA8
#define GL_RGBA8				0x8058
#endif

CRAFT_TYPE_DEFINE(SkBitmap)
{
	_.add<GraphPropertyName>("cult/bitmap");
	_.add<GraphPropertyCppName>("::SkBitmap");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkBitmap> _this) {
		return "Tag";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkBitmap> _this) {
		return "Tag";
	});
}

CRAFT_TYPE_DEFINE(SkImage)
{
	_.add<GraphPropertyName>("cult/image");
	_.add<GraphPropertyCppName>("::SkImage");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkImage> _this) {
		return "SkImage";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkImage> _this) {
		return "SkImage";
	});
}

CRAFT_TYPE_DEFINE(GrContext)
{
	_.add<GraphPropertyName>("cult/bitmap");
	_.add<GraphPropertyCppName>("::GrContext");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<GrContext> _this) {
		return "Tag";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<GrContext> _this) {
		return "Tag";
	});
}


CRAFT_TYPE_DEFINE(SkSurface)
{
	_.add<GraphPropertyName>("cult/image");
	_.add<GraphPropertyCppName>("::SkSurface");
	_.use<PStringer>().singleton<FunctionalStringer>([](::craft::instance<SkSurface> _this) {
		return "SkSurface";
	});
	_.use<PRepr>().singleton<FunctionalRepr>([](::craft::instance<SkSurface> _this) {
		return "SkSurface";
	});
}

//https://gist.github.com/ad8e/dd150b775ae6aa4d5cf1a092e4713add

void cultlang::draw::make_backing_bindings(craft::types::instance<craft::lisp::Module> m)
{
	auto semantics = m->require<CultSemantics>();

	LMM(DP"/Context", []() { 
		GrContextOptions options;
		options.fRequireDecodeDisableForSRGB = false;
		auto sContext = GrContext::MakeGL(nullptr, options);//.release();
		sContext->ref();
		return instance<GrContext>::makeFromPointerAndMemoryManager(sContext.get(), +[](void* p) { ((GrContext*)p)->unref(); });
	});
	LMM(DP"/Context/flush", [](instance<GrContext> context) {context->flush(); });



	LMM(DP"/Surface", [](instance<GrContext> context, instance<int32_t> width, instance<int32_t> height) { 
		GrGLFramebufferInfo framebufferInfo;
		framebufferInfo.fFBOID = 0; // assume default framebuffer
		// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
		//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
		framebufferInfo.fFormat = GL_RGBA8;

		SkColorType colorType;
		if (kRGBA_8888_GrPixelConfig == kSkia8888_GrPixelConfig) {
			colorType = kRGBA_8888_SkColorType;
		}
		else {
			colorType = kBGRA_8888_SkColorType;
		}
		GrBackendRenderTarget backendRenderTarget(*width, *height,
			0, // sample count
			0, // stencil bits
			framebufferInfo);

		
		auto gpuSurface = SkSurface::MakeFromBackendRenderTarget(context.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr);
		if (!gpuSurface) {
			throw stdext::exception("SkSurface::MakeRenderTarget returned null");
		}
		
		gpuSurface->ref();
		return instance<SkSurface>::makeFromPointerAndMemoryManager(gpuSurface.get(), +[](void* p) { ((SkSurface*)p)->unref(); });
	});
}