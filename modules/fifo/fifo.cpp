#include <iostream>
#include <stdexcept>
#include "fifo.hpp"

using modular::Package;
using modular::PackagePtr;
using modular::Processor;
using modular::ProcessorInstance;
using modular::ProcessorInstancePtr;
using modular::ProcessorParams;


class FifoWriterProcessorInstance : public ProcessorInstance {
public:
  FifoWriterProcessorInstance(const ProcessorParams& params):
    ProcessorInstance(0, 1)
  {

  }

  void process() override {}

private:
};


class FifoReaderProcessorInstance : public ProcessorInstance {
public:
  FifoReaderProcessorInstance(const ProcessorParams& params):
    ProcessorInstance(0, 1)
  {

  }

  void process() override {}

private:
};


class FifoWriterProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<FifoWriterProcessorInstance>(params);
  }
};


class FifoReaderProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<FifoReaderProcessorInstance>(params);
  }
};


void init(Context& context) {
  std::cout << "fifo:initializing" << std::endl;
  context.processors().add("fifo::writer", std::make_shared<FifoWriterProcessor>());
  context.processors().add("fifo::reader", std::make_shared<FifoReaderProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
