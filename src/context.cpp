#include "modular/context.hpp"
#include "modular/loader.hpp"

namespace modular {

Context::Context(Scheduler& scheduler):
  _scheduler(scheduler),
  _loader_p(std::make_unique<Loader>(*this)) {}

}
