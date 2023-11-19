#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <modular/modular.hpp>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Load path is required" << std::endl;
    return 0;
  }

  modular::Context context;
  context.loader().add_path(argv[1]);
  context.loader().load("fifo");

  pid_t pid = fork();
  if (pid != 0) {
    modular::Graph graph;
    auto writer1 = graph.add(context.processors().get("fifo::writer"));

  } else {
    modular::Graph graph;
    auto reader1 = graph.add(context.processors().get("fifo::reader"));

  }
}
