#pragma once
#include <filesystem>
#include "string.hpp"
#include "utils/lib.hpp"

namespace modular {

class Library;
using LibraryPtr = std::shared_ptr<Library>;

class Library {
public:
  using Handle = void*;
  using Path = std::filesystem::path;

  explicit Library(const Path& path):
    _handle(utils::lib::open(path)) {}

  ~Library() {
    if (_handle)
      utils::lib::close(_handle);
  }

  template<typename T>
  T find(const String& name, bool required = false) {
    void* sym = utils::lib::find(_handle, name);
    if (required and !sym)
      throw std::runtime_error("Symbol not found");
    return reinterpret_cast<T>(sym);
  }

private:
  Handle _handle;
};

}
