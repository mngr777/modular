#pragma once
#include <memory>
#include "slot.hpp"

namespace modular {

class ProcessorInstance;
using ProcessorInstancePtr = std::unique_ptr<ProcessorInstance>;

class Processor;
using ProcessorPtr = std::shared_ptr<Processor>;


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

  virtual ProcessorInstancePtr instance() = 0;
};

}
