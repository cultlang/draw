#include "draw/all.h"

#include "draw/cult/backing.h"
#include "draw/cult/color.h"
#include "draw/cult/rect.h"
#include "draw/cult/rrect.h"
#include "draw/cult/irect.h"
#include "draw/cult/path.h"
#include "draw/cult/ipoint.h"
#include "draw/cult/point.h"
#include "draw/cult/paint.h"
#include "draw/cult/canvas.h"
#include "lisp/semantics/cult/calling.h"

using namespace cultlang;
using namespace cultlang::draw;

CULTLANG_DRAW_EXPORTED extern craft::lisp::BuiltinModuleDescription DrawModule("cult/draw", &make_draw_bindings);
void cultlang::draw::make_draw_bindings(craft::types::instance<craft::lisp::Module> m)
{
	make_backing_bindings(m);
	make_canvas_bindings(m);
	make_color_bindings(m);
	make_irect_bindings(m);
	make_point_bindings(m);
	make_path_bindings(m);
	make_shader_bindings(m);
	make_paint_bindings(m);
	make_rect_bindings(m);
	make_rrect_bindings(m);
}


/******************************************************************************
** DLL ENTRY
******************************************************************************/

#include "types/dll_entry.inc"