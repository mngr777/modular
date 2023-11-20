#include <chrono>
#include <iostream>
#include <thread>
#include <sys/types.h>
#include <unistd.h>
#include <modular/modular.hpp>

const modular::String FifoName("/tmp/fifo-ipc1");


int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Load path is required" << std::endl;
    return 0;
  }

  modular::Context context;
  context.loader().add_path(argv[1]);
  context.loader().load("text");
  context.loader().load("fifo");

  pid_t pid = fork();
  if (pid != 0) {
    modular::Graph graph;
    auto spam = context.processors().get("text::spam");
    auto write = context.processors().get("fifo::write");
    auto spam1 = graph.add(spam, {{"text", "spam, spam, spam, spam!"}});
    auto spam2 = graph.add(spam);
    auto write1 = graph.add(write, {{"path", FifoName}});
    spam1->connect(write1, 0, 0);
    spam2->connect(write1, 0, 0);

    for (int i = 0; i < 10; i++) {
      spam1->process();
      spam2->process();
      while (graph.update()) {}
    }

  } else {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    modular::Graph graph;
    auto read = context.processors().get("fifo::read");
    auto print = context.processors().get("text::print");
    auto read1 = graph.add(read, {{"path", FifoName}});
    auto print1 = graph.add(print);
    read1->connect(print1, 0, 0);

    for (int i = 0; i < 21; i++) {
      read1->process();
      while (graph.update()) {}
    }
  }
}
