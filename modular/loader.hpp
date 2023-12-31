#pragma once
#include <filesystem>
#include <list>
#include "string.hpp"

namespace modular {

class Context;

class Loader {
public:
  explicit Loader(Context& context):
    _context(context) {}

  using Path = std::filesystem::path;

  void add_path(Path path);

  void load(const String& name);

private:
  void do_load(const String& name, const Path& path);

  Context& _context;
  std::list<Path> _paths;
};

}
