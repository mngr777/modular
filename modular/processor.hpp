#pragma once
#include <memory>
#include "slot.hpp"

namespace modular {

class ProcessorInstance;
using ProcessorInstancePtr = std::unique_ptr<ProcessorInstance>;

class ProcessorInstance {
public:
  ProcessorInstance(
    SlotList::Size input_num,
    SlotList::Size output_num):
    _inputs(input_num),
    _outputs(output_num) {}

  virtual ~ProcessorInstance() {}

  virtual void exec() = 0;

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
