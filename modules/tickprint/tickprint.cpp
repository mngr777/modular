#include <iostream>
#include "tickprint.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::Processor;
using modular::ProcessorInstance;
using modular::ProcessorInstancePtr;
using modular::ProcessorParams;
using modular::read_package;

class TickprintProcessorInstance : public ProcessorInstance {
public:
  TickprintProcessorInstance():
    ProcessorInstance(1, 0) {}

  void process() override {
    PackagePtr package = input(0).value();
    if (!package)
      return;
    auto tick = read_package<unsigned>(package);
    std::cout << "tick: " << tick << std::endl;
  }
};


class TickprintProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<TickprintProcessorInstance>();
  }
};


void init(Context& context) {
  std::cout << "tickprint::initializing" << std::endl;
  context.processors().add("tickprint::print", std::make_shared<TickprintProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
