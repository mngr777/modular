#pragma once
#include <filesystem>
#include "../string.hpp"

namespace modular {
namespace utils {
namespace lib {

String filename(String name);

void* open(const std::filesystem::path& path);

void close(void* handle);

void* find(void* handle, const String& name);

}}}
