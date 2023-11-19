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

  Package(Size size): _data(std::make_unique<Byte[]>(size)) {}

  template<typename T>
  Package(): Package(sizeof(T)) {}

  template<typename T>
  T& get() {
    return reinterpret_cast<T>(*data());
  }

  template<typename T>
  const T& get() const {
    return reinterpret_cast<T>(*data());
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
