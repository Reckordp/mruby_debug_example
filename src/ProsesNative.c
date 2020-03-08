#include <stdio.h>
#include <stdlib.h>
#include <mruby.h>
#include <mruby/compile.h>
#include <mruby/irep.h>
#include <mruby/debug.h>
#include <mruby/proc.h>

mrb_value getCurrentFile(mrb_state *mrb, mrb_value self) {
	struct RProc *proc_ptr;
	mrb_irep *irep;
	mrb_callinfo *ci;
	const char *filename_c;
	filename_c = NULL;

	ci = mrb->c->ci;
	ci--;

	proc_ptr = ci->proc;
	if (MRB_METHOD_CFUNC_P(proc_ptr)) return mrb_str_new_lit(mrb, "(unknown)");

	irep = proc_ptr->body.irep;
	filename_c = mrb_debug_get_filename(mrb, irep, mrb->c->ci->pc - irep->iseq);
	return mrb_str_new_cstr(mrb, filename_c);
}

mrb_value getCurrentLine(mrb_state *mrb, mrb_value self) {
	struct RProc *proc_ptr;
	mrb_irep *irep;
	mrb_callinfo *ci;
	int lineno;
	lineno = -1;

	ci = mrb->c->ci;
	ci--;

	proc_ptr = ci->proc;
	if (MRB_METHOD_CFUNC_P(proc_ptr)) return mrb_str_new_lit(mrb, "(unknown)");

	irep = proc_ptr->body.irep;
	lineno = mrb_debug_get_line(mrb, irep, mrb->c->ci->pc - irep->iseq);
	return mrb_fixnum_value(lineno);
}

int main() {
	mrb_state *mrb;
	struct RClass *responsible;
	mrbc_context *c;
	FILE *fp;
	char filename[64];

	mrb = mrb_open();
	responsible = mrb_define_module(mrb, "Responsible");
	mrb_define_class_method(mrb, responsible, "fileNow", (mrb_func_t)getCurrentFile, MRB_ARGS_NONE());
	mrb_define_class_method(mrb, responsible, "lineNow", (mrb_func_t)getCurrentLine, MRB_ARGS_NONE());

	strcpy(filename, "rubyFile.rb");
	c = malloc(sizeof(mrbc_context));
	memset(c, 0, sizeof(mrbc_context));

	mrbc_filename(mrb, c, filename);

	fp = fopen(filename, "r");
	mrb_load_file_cxt(mrb, fp, c);
	fclose(fp);

	free(c);

	mrb_close(mrb);
	return 0;
}