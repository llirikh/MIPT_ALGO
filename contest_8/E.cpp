#include <algorithm>
#include <iostream>
#include <vector>

struct Solver {
  struct Edge {
    int from, to, cost;
  };

  const int kMaxVertex = 100000;
  const int kInfinity = 1e9;

  int vertex_umber;
  int edge_umber;
  std::vector<Edge> edge;

  void Read();
  void Solve();
};

void Solver::Read() {
  std::cin >> vertex_umber;
  vertex_umber += 2;
  edge_umber = 0;
  for (int i = 0; i < vertex_umber; ++i) {
    edge.push_back({0, i, 0});
    ++edge_umber;
  }
  for (int i = 0; i < vertex_umber; ++i) {
    edge.push_back({1, i, 0});
    ++edge_umber;
  }
  for (int i = 2; i < vertex_umber; ++i) {
    for (int j = 2; j < vertex_umber; ++j) {
      int from;
      std::cin >> from;
      if (from != kMaxVertex) {
        edge.push_back({i, j, from});
        ++edge_umber;
      }
    }
  }
}

void Solver::Solve() {
  Read();

  std::vector<int> distantion(vertex_umber);
  std::vector<int> previous(vertex_umber, -1);
  int x_vertex = -1;
  for (int i = 0; i < vertex_umber; ++i) {
    x_vertex = -1;
    for (int j = 0; j < edge_umber; ++j) {
      if (distantion[edge[j].to] > distantion[edge[j].from] + edge[j].cost) {
        distantion[edge[j].to] = std::max(-kInfinity, distantion[edge[j].from] + edge[j].cost);
        previous[edge[j].to] = edge[j].from;
        x_vertex = edge[j].to;
      }
    }
  }
  if (x_vertex == -1) {
    std::cout << "NO";
  } else {
    int y_vertex = x_vertex;
    for (int i = 0; i < vertex_umber; ++i) {
      y_vertex = previous[y_vertex];
    }
    std::vector<int> path;
    for (int current = y_vertex;; current = previous[current]) {
      path.push_back(current);
      if (current == y_vertex && path.size() > 1) {
        break;
      }
    }
    std::reverse(path.begin(), path.end());

    std::cout << "YES" << '\n';
    std::cout << path.size() << '\n';
    for (int item : path) {
      std::cout << item - 1 << ' ';
    }
  }
}

int main() {
  Solver solver;
  solver.Solve();
}