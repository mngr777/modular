#pragma once
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "string.hpp"

namespace modular {

template<typename T>
class Registry {
public:
  using Item = T;
  using ItemPtr = std::shared_ptr<Item>;

  void add(const String& name, ItemPtr item) {
    auto res = _map.emplace(name, item);
    if (!res.second)
      throw std::runtime_error("Already added");
  }

  ItemPtr get(const String& name) {
    return _map.at(name);
  }

private:
  using Map = std::unordered_map<String, ItemPtr>;

  Map _map;
};

}
