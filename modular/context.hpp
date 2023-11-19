#pragma once
#include "module.hpp"
#include "processor.hpp"
#include "registry.hpp"

namespace modular {

class Loader;

class Context {
public:
  Context();

  Registry<Module>& modules() {
    return _modules;
  }

  Registry<Processor>& processors() {
    return _processors;
  }

  Loader& loader() {
    return *_loader_p;
  }

private:
  Registry<Module> _modules;
  Registry<Processor> _processors;
  std::unique_ptr<Loader> _loader_p;
};

}
