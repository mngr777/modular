#include <stdexcept>
#include "modular/graph.hpp"

namespace modular {

// Node

void Graph::Node::connect(Graph::NodePtr other, unsigned output, unsigned input) {
  if (output >= _processor->outputs().num())
    throw std::runtime_error("invalid output index");
  if (input >= other->_processor->inputs().num())
    throw std::runtime_error("invalid input index");

  other->_incoming_num++;

  _connections.push_back(
    (Connection) {.other = other, .output = output, .input = input});
}


void Graph::Node::process() {
  std::lock_guard lock(_process_mutex);
  do_process();
  _processor->inputs().reset();
}


void Graph::Node::update_and_process(unsigned input, PackagePtr value) {
  std::lock_guard lock(_process_mutex);
  _processor->input(input).update(value);
  do_process();
  _processor->inputs().reset();
}



void Graph::Node::do_process() {
  _processor->process();

  for (auto& conn : _connections) {
    Slot& output = _processor->output(conn.output);
    if (!output.is_updated())
      continue;
    _graph.push_update(conn.other, conn.input, output.value());
  }
}

// Graph

Graph::NodePtr Graph::add(Processor& processor, const ProcessorParams& params) {
  auto node = std::make_shared<Node>(*this, processor, params);
  _nodes.push_back(node);
  return node;
}


void Graph::connect(
  Graph::NodePtr from, unsigned output,
  Graph::NodePtr to, unsigned input)
{
  from->connect(to, output, input);
}


bool Graph::update() {
  Update update = {0};
  {
    std::lock_guard lock(_updates_mutex);
    if (_updates.size() == 0)
      return false;
    update = _updates.front();
    _updates.pop();
  }
  apply_update(update);
  return true;
}


void Graph::wait_update() {
  std::unique_lock lock(_updates_mutex);
  if (_updates.size() > 0) {
    lock.unlock();
    update();
    return;
  }
  _updates_cond.wait(lock, [=]() { return _updates.size() > 0; });
  update();
}


void Graph::push_update(NodePtr node, unsigned input, PackagePtr value) {
  {
    std::lock_guard lock(_updates_mutex);
    _updates.push((Update) {.node = node, .input = input, .value = value});
  }
  _updates_cond.notify_one();
}


void Graph::apply_update(Update& update) {
  update.node->update_and_process(update.input, update.value);
}

}
