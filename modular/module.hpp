#pragma once
#include <memory>
#include "library.hpp"

namespace modular {

class Context;
class Module;
using ModulePtr = std::shared_ptr<Module>;

class Module {
public:
  using InitProc = void(*)(Context&);
  using CleanupProc = void(*)(Context&);

  Module(Context& context, LibraryPtr library);
  ~Module();

private:
  void init();
  void cleanup();

  Context& _context;
  LibraryPtr _library;
  InitProc _init_proc;
  CleanupProc _cleanup_proc;
};

}
