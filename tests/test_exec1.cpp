#include <iostream>
#include <modular/modular.hpp>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Load path is required" << std::endl;
    return 0;
  }

  modular::Context context;
  context.loader().add_path(argv[1]);
  context.loader().load("tick");
  context.loader().load("tickprint");

  auto tick = context.processors().get("tick::tick");
  auto tickprint = context.processors().get("tickprint::print");

  modular::Graph graph;
  auto tick1 = graph.add(tick);
  auto tick2 = graph.add(tick, {{"start", 10u}});
  auto tickprint1 = graph.add(tickprint);
  tick1->connect(tickprint1, 0, 0);
  tick2->connect(tickprint1, 0, 0);

  for (int i = 0; i < 10; i++) {
    tick1->process();
    tick2->process();
    while (graph.update()) {}
  }
}
