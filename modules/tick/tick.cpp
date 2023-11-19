#include <iostream>
#include "tick.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::ProcessorInstancePtr;

class TickProcessorInstance : public modular::ProcessorInstance {
public:
  TickProcessorInstance():
    modular::ProcessorInstance(0, 1),
    _tick(0) {}

  void process() override {
    PackagePtr pkg = Package::make<unsigned>();
    pkg->set<unsigned>(++_tick);
    output(0).update(pkg);
  }

private:
  unsigned _tick;
};


class TickProcessor : public modular::Processor {
public:
  ProcessorInstancePtr instance() override {
    return std::move(std::make_unique<TickProcessorInstance>());
  }
};


void init(Context& context) {
  std::cout << "tick::initializing" << std::endl;
  context.processors().add("tick::tick", std::make_shared<TickProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
