#pragma once
#include "module.hpp"
#include "processor.hpp"
#include "registry.hpp"

namespace modular {

class Loader;
class Scheduler;

class Context {
public:
  Context(Scheduler& scheduler);

  Scheduler& scheduler() {
    return _scheduler;
  }

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
  Scheduler& _scheduler;
  Registry<Module> _modules;
  Registry<Processor> _processors;
  std::unique_ptr<Loader> _loader_p;
};

}
