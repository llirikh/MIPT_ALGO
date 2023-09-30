#include <iostream>
#include <vector>

const int INF = 1e9;

struct Edge {
  int weight;
  int indexTo;
};

struct Node {
  int idx;
  std::vector<Edge> edges;

  int prevIdx;
  int weight;
  bool visited;
};

struct Graph {
  std::vector<Node> nodes;

  void clear() {nodes.clear();}
  void clear_edges() {
    for (auto& node: nodes) {
      node.edges.clear();
    }
  }
  void init_start_values() {
    for (auto& node: nodes) {
      node.weight = INF;
      node.visited = false;
      node.prevIdx = -1;
    }
  }
};