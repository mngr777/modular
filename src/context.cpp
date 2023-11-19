#include "modular/context.hpp"
#include "modular/loader.hpp"

namespace modular {

Context::Context():
  _loader_p(std::make_unique<Loader>(*this)) {}

}
