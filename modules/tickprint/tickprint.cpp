#include <iostream>
#include "tickprint.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::ProcessorInstancePtr;

class TickprintProcessorInstance : public modular::ProcessorInstance {
public:
  TickprintProcessorInstance():
    modular::ProcessorInstance(1, 0) {}

  void process() override {
    PackagePtr pkg = input(0).value();
    if (!pkg)
      return;
    unsigned tick = pkg->get<unsigned>();
    std::cout << "tick: " << tick << std::endl;
  }
};


class TickprintProcessor : public modular::Processor {
public:
  ProcessorInstancePtr instance() override {
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
