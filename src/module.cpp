#include "modular/module.hpp"
#include "modular/string.hpp"

namespace modular {

static const Char InitProcName[]    = MODULAR_TEXT("init");
static const Char CleanupProcName[] = MODULAR_TEXT("cleanup");


Module::Module(Context& context, LibraryPtr library):
  _context(context),
  _library(library),
  _init_proc(library->find<InitProc>(InitProcName, true)),
  _cleanup_proc(library->find<CleanupProc>(CleanupProcName, true))
{
  init();
}


Module::~Module() {
  cleanup();
}


void Module::init() {
  _init_proc(_context);
}


void Module::cleanup() {
  _cleanup_proc(_context);
}

}
