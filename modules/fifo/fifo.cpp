#include <iostream>
#include <fstream>
#include <stdexcept>
#include "fifo.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using modular::Package;
using modular::PackagePtr;
using modular::Processor;
using modular::ProcessorInstance;
using modular::ProcessorInstancePtr;
using modular::ProcessorParams;
using modular::String;
using modular::read_package;
using modular::write_package;


class FifoProcessorInstance : public ProcessorInstance {
public:
  using ProcessorInstance::ProcessorInstance;

protected:
  void read_path(const ProcessorParams& params) {
    if (!params.has("path"))
      throw std::invalid_argument("path parameter is required");
    _path = params.get<String>("path");
  }

  String _path;
};


class FifoWriteProcessorInstance : public FifoProcessorInstance {
public:
  FifoWriteProcessorInstance(const ProcessorParams& params):
    FifoProcessorInstance(1, 0)
  {
    // Get pipe path
    read_path(params);

    // Make FIFO pipe
    int ret = mkfifo(_path.c_str(), S_IRWXU);
    if (ret != 0 && errno != EEXIST)
      throw std::runtime_error("failed to create a pipe");

    // Open to write
    _pipe.open(_path, std::ios::out | std::ios::binary);
    if (!_pipe.is_open())
      throw std::runtime_error("failed to open output pipe");
  }

  void process() override {
    PackagePtr package = input(0).value();
    if (!package)
      return;
    if (package->size() == 0) {
      std::cout << "zero length package!" << std::endl;
      return;
    }
    write_package(_pipe, package);
  }
private:
  std::fstream _pipe;
};


class FifoReadProcessorInstance : public FifoProcessorInstance {
public:
  FifoReadProcessorInstance(const ProcessorParams& params):
    FifoProcessorInstance(0, 1)
  {
    // Get pipe path
    read_path(params);

    // Open to read
    _pipe.open(_path, std::ios::in | std::ios::binary);
    if (!_pipe.is_open())
      throw std::runtime_error("failed to open input pipe");
  }

  void process() override {
    PackagePtr package = read_package(_pipe);
    if (!package) {
      // std::cout << "no packages in the pipe" << std::endl;
      return;
    }
    output(0).update(package);
  }

private:
  std::fstream _pipe;
};


class FifoWriteProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<FifoWriteProcessorInstance>(params);
  }
};


class FifoReadProcessor : public Processor {
public:
  ProcessorInstancePtr instance(const ProcessorParams& params = ProcessorParams()) override {
    return std::make_unique<FifoReadProcessorInstance>(params);
  }
};


void init(Context& context) {
  std::cout << "fifo:initializing" << std::endl;
  context.processors().add("fifo::write", std::make_shared<FifoWriteProcessor>());
  context.processors().add("fifo::read", std::make_shared<FifoReadProcessor>());
}


void cleanup(Context& context) {
  // TODO
}
