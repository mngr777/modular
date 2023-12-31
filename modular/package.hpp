#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <istream>
#include <memory>
#include <ostream>
#include "string.hpp"

// TODO: refactoring, move getters/setters out

namespace modular {

class Package;
using PackagePtr = std::shared_ptr<Package>;

class Package {
public:
  using Size = std::size_t;
  using Byte = std::uint8_t;
  using Data = Byte*;

  static PackagePtr make(Size size) {
    return std::make_shared<Package>(size);
  }

  template<typename T>
  static PackagePtr make() {
    auto pkg = make(sizeof(T));
    pkg->get<T>() = T();
    return pkg;
  }

  Package(Size size):
    _size(size),
    _data(std::make_unique<Byte[]>(size)) {}

  template<typename T>
  void set(const T& value) {
    get<T>() = value;
  }

  template<typename T>
  T& get() {
    return *reinterpret_cast<T*>(data());
  }

  template<typename T>
  const T& get() const {
    return *reinterpret_cast<T*>(data());
  }

  const Size size() const {
    return _size;
  }

  Data data() {
    return _data.get();
  }

  const Data data() const {
    return _data.get();
  }

  template<typename T>
  T* data() {
    return reinterpret_cast<T*>(_data.get());
  }

  template<typename T>
  const T* data() const {
    return reinterpret_cast<T*>(_data.get());
  }

private:
  Size _size;
  std::unique_ptr<Byte[]> _data;
};


template<typename T>
PackagePtr make_package(const T& value) {
  PackagePtr package = std::make_shared<Package>(sizeof(value));
  package->set<T>(value);
  return package;
}


template<typename T>
T package_data(const Package& package) {
  return package.get<T>();
}


template<typename T>
T package_data(const PackagePtr package) {
  return package_data<T>(*package);
}


template<>
PackagePtr make_package(const String& value);

template<>
String package_data<String>(const Package& package);


void write_package(std::ostream& os, Package& package);

inline void write_package(std::ostream& os, PackagePtr package) {
  write_package(os, *package);
}

PackagePtr read_package(std::istream& is);

}
