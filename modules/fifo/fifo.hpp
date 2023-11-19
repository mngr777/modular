#pragma once
#include "modular/modular.hpp"

using modular::Context;

extern "C" {

void init(Context& context);

void cleanup(Context& context);

}
