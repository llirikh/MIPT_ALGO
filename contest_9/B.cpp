#include <iostream>
#include <vector>

struct Edge {
  int v1;
  int v2;
  int w;
};

int getRoot(int v, std::vector<int>& parent) {
  if (parent[v] < 0) {
    return v;
  } else {
    int root = getRoot(parent[v], parent);
    parent[v] = root;
    return root;
  }
}

bool join(int a, int b, std::vector<int>& parent) {
  a = getRoot(a, parent);
  b = getRoot(b, parent);
  if (a == b) {
    return false;
  }
  if (parent[a] < parent[b]) {
    parent[a] += parent[b];
    parent[b] = a;
  } else {
    parent[b] += parent[a];
    parent[a] = b;
  }
  return true;
}

int main() {
  int nV, nE;
  std::cin >> nV >> nE;
  std::vector<std::vector<Edge>> edges(1 + 100000);
  for (int i = 0; i < nE; ++i) {
    int v1, v2, w;
    std::cin >> v1 >> v2 >> w;
    edges[w].push_back(Edge{v1, v2, w});
  }
  std::vector<int> parent(1 + nV, -1); // parent[v] >= 0 - parent_node || parent[v] < 0 - -size of root
  int sum = 0;
  for (auto const &list : edges) {
    for (const Edge &e : list) {
      if (join(e.v1, e.v2, parent)) {
        sum += e.w;
      }
    }
  }
  std::cout << sum;
}