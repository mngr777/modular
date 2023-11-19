#pragma once
#include <condition_variable>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include "processor.hpp"

namespace modular {

class Graph {
public:
  class Node;
  using NodePtr = std::shared_ptr<Node>;
  using NodeList = std::list<NodePtr>;

  class Node {
  public:
    Node(Graph& graph, Processor& processor):
      _graph(graph),
      _processor(processor.instance()),
      _incoming_num(0) {}

    void connect(NodePtr other, unsigned output, unsigned input);

    void process();

    void update_and_process(unsigned input, PackagePtr value);

    ProcessorInstance& processor() {
      return *_processor;
    }

  private:
    struct Connection {
      NodePtr other;
      unsigned output;
      unsigned input;
    };

    void do_process();

    Graph& _graph;
    ProcessorInstancePtr _processor;
    unsigned _incoming_num;
    std::list<Connection> _connections;
    std::mutex _process_mutex;
  };

  NodePtr add(ProcessorPtr processor) {
    return add(*processor);
  }

  NodePtr add(Processor& processor);

  void connect(
    NodePtr from, unsigned output,
    NodePtr to, unsigned input);

  bool update();

  void wait_update();

  NodeList& nodes() {
    return _nodes;
  }

  const NodeList& nodes() const {
    return _nodes;
  }

private:
  struct Update {
    NodePtr node;
    unsigned input;
    PackagePtr value;
  };

  void push_update(NodePtr node, unsigned input, PackagePtr value);

  void apply_update(Update& update);

  std::list<NodePtr> _nodes;
  std::queue<Update> _updates;
  std::mutex _updates_mutex;
  std::condition_variable _updates_cond;
};

}
