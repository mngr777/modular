#pragma once
#include <vector>
#include "package.hpp"

namespace modular {

class Slot {
public:
  Slot(): _updated(false) {}

  void update(PackagePtr package) {
    // Check if reset??
    _value = package;
    _updated = true;
  }

  void reset() {
    _value.reset();
    _updated = false;
  }

private:
  bool _updated;
  PackagePtr _value;
};


class SlotList {
public:
  using Size = unsigned;

  SlotList(Size size): _slots(size) {}

  const Size size() const {
    return static_cast<Size>(_slots.size());
  }

  auto& operator[](Size n) {
    return _slots.at(n);
  }

  const auto& operator[](Size n) const {
    return _slots.at(n);
  }

  auto begin() {
    return _slots.begin();
  }

  auto end() {
    return _slots.begin();
  }

  const auto begin() const {
    return _slots.begin();
  }

  const auto end() const {
    return _slots.begin();
  }

private:
  std::vector<Slot> _slots;
};

}
