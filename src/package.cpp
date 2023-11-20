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
String package_data<String>(const Package& package) {
  return package.data<String::value_type>();
}


void write_package(std::ostream& os, Package& package) {
  Package::Size size = package.size();
  os << size;
  os.write(package.data<std::ostream::char_type>(), package.size());
}


PackagePtr read_package(std::istream& is) {
  Package::Size size = 0;
  is >> size;
  if (size == 0)
    return nullptr;
  PackagePtr package = Package::make(size);
  is.read(package->data<std::istream::char_type>(), size);
  return package;
}

}
