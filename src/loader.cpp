#include <algorithm>
#include <memory>
#include <stdexcept>
#include "modular/context.hpp"
#include "modular/library.hpp"
#include "modular/loader.hpp"
#include "modular/module.hpp"
#include "modular/utils/lib.hpp"

namespace fs = std::filesystem;

namespace modular {

void Loader::add_path(Loader::Path path) {
  auto it = std::find(_paths.begin(), _paths.end(), path);
  if (it == _paths.end())
    _paths.push_front(path);
}


void Loader::load(const String& name) {
  for (const auto& dir : _paths) {
    auto path = dir / utils::lib::filename(name);
    if (fs::exists(path)) {
      do_load(name, path);
      return;
    }
  }
  throw std::runtime_error("library not found");
}


void Loader::do_load(const String& name, const Path& path) {
  auto library = std::make_shared<Library>(path);
  auto module = std::make_shared<Module>(_context, library);
  _context.modules().add(name, module);
}

}
