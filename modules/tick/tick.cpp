#include <iostream>
#include "tick.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::Processor;
using modular::ProcessorInstance;
using modular::ProcessorInstancePtr;
using modular::ProcessorParams;
using modular::make_package;


class TickProcessorInstance : public ProcessorInstance {
public:
  TickProcessorInstance(const ProcessorParams& params):
    ProcessorInstance(0, 1),
    _tick(0)
  {
    if (params.has("start"))
      _tick = params.get<unsigned>("start");
  }

  void process() override {
    PackagePtr package = make_package<unsigned>(_tick++);
    output(0).update(package);
  }

private:
  unsigned _tick;
};


class TickProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<TickProcessorInstance>(params);
  }
};


void init(Context& context) {
  std::cout << "tick::initializing" << std::endl;
  context.processors().add("tick::tick", std::make_shared<TickProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
