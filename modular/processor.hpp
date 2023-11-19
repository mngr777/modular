#pragma once
#include <initializer_list>
#include <memory>
#include <unordered_map>
#include <variant>
#include "slot.hpp"
#include "string.hpp"

namespace modular {

class ProcessorInstance;
using ProcessorInstancePtr = std::unique_ptr<ProcessorInstance>;

class Processor;
using ProcessorPtr = std::shared_ptr<Processor>;


class ProcessorParams {
public:
  using Value = std::variant<bool, int, unsigned, float, String>;
  using Map = std::unordered_map<String, Value>;

  ProcessorParams() {}
  ProcessorParams(std::initializer_list<Map::value_type> values):
    _params(values) {}

  const bool has(const String& key) const {
    return _params.count(key) > 0;
  }

  template<typename T>
  const T get(const String& key) const {
    return std::get<T>(_params.at(key));
  }

  template<typename T>
  void set(const String& key, const T& value) {
    _params[key] = value;
  }

private:
  Map _params;
};


class ProcessorInstance {
public:
  ProcessorInstance(
    SlotList::Size input_num,
    SlotList::Size output_num):
    _inputs(input_num),
    _outputs(output_num) {}

  virtual ~ProcessorInstance() {}

  virtual void process() = 0;

  Slot& input(unsigned n) {
    return _inputs[n];
  }

  Slot& output(unsigned n) {
    return _outputs[n];
  }

  const Slot& input(unsigned n) const {
    return _inputs[n];
  }

  const Slot& output(unsigned n) const {
    return _outputs[n];
  }

  SlotList& inputs() {
    return _inputs;
  }

  SlotList& outputs() {
    return _outputs;
  }

  const SlotList& inputs() const {
    return _inputs;
  }

  const SlotList& outputs() const {
    return _outputs;
  }

private:
  SlotList _inputs;
  SlotList _outputs;
};


class Processor {
public:
  virtual ~Processor() {}

  virtual ProcessorInstancePtr instance(const ProcessorParams& params) = 0;
};

}
