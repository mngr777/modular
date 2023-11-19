#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>

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

  Package(Size size): _data(std::make_unique<Byte[]>(size)) {}

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

  const Data data() const {
    return _data.get();
  }

  Data data() {
    return _data.get();
  }

private:
  Size _size;
  std::unique_ptr<Byte[]> _data;
};

}
