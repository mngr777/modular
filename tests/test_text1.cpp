#include <iostream>
#include <modular/modular.hpp>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Load path is required" << std::endl;
    return 0;
  }

  modular::Context context;
  context.loader().add_path(argv[1]);
  context.loader().load("text");

  auto print = context.processors().get("text::print");
  auto spam = context.processors().get("text::spam");

  modular::Graph graph;
  auto spam1 = graph.add(spam, {{"text", "spam, spam, spam, spam!"}});
  auto spam2 = graph.add(spam);
  auto print1 = graph.add(print);
  spam1->connect(print1, 0, 0);
  spam2->connect(print1, 0, 0);

  for (int i = 0; i < 10; i++) {
    spam1->process();
    spam2->process();
    while (graph.update()) {}
  }
}
