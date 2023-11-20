#include <iostream>
#include "text.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::Processor;
using modular::ProcessorInstance;
using modular::ProcessorInstancePtr;
using modular::ProcessorParams;
using modular::String;
using modular::make_package;
using modular::package_data;


class PrintProcessorInstance : public ProcessorInstance {
public:
  PrintProcessorInstance():
    ProcessorInstance(1, 0) {}

  void process() override {
    PackagePtr package = input(0).value();
    if (!package)
      return;
    auto value = package_data<String>(package);
    std::cout << ">> " << value << std::endl;
  }
};


class SpamProcessorInstance : public ProcessorInstance {
public:
  SpamProcessorInstance(const ProcessorParams& params):
    ProcessorInstance(0, 1),
    _text(params.has("text") ? params.get<String>("text") : String("lovely spam!")) {}

  void process() override {
    output(0).update(make_package(_text));
  }

private:
  String _text;
};


class PrintProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<PrintProcessorInstance>();
  }
};


class SpamProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<SpamProcessorInstance>(params);
  }
};


void init(Context& context) {
  std::cout << "text::initializing" << std::endl;
  context.processors().add("text::print", std::make_shared<PrintProcessor>());
  context.processors().add("text::spam", std::make_shared<SpamProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
