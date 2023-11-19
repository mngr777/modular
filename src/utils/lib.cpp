#include "modular/utils/lib.hpp"
#include <dlfcn.h>

namespace fs = std::filesystem;

namespace modular {
namespace utils {
namespace lib {

String filename(String name) {
  return name + ".so";
}


void* open(const std::filesystem::path& path) {
  void* handle = dlopen(path.c_str(), RTLD_NOW);
  if (!handle) {
    std::string message("Failed to load library ");
    message += path.string() + ", " + dlerror();
    throw std::runtime_error(message);
  }
  return handle;
}


void close(void* handle) {
  dlclose(handle);
}


void* find(void* handle, const String& name) {
  return dlsym(handle, name.c_str());
}

}}}
