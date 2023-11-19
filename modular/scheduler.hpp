#pragma once
#include <functional>

namespace modular {

class Scheduler {
public:
  using Task = std::function<void(void)>;

  virtual ~Scheduler() {}

  virtual void add(Task task) = 0;
};

}
