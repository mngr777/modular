#include "modular/package.hpp"

namespace modular {

template<>
PackagePtr make_package(const String& value) {
  Package::Size size = (value.size() + 1) * sizeof(String::value_type);
  PackagePtr package = std::make_shared<Package>(size);
  std::memcpy(package->data(), value.c_str(), size);
  return package;
}


template<>
String read_package<String>(const Package& package) {
  return package.data<String::value_type>();
}

}
