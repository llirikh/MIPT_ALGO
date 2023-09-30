#include <iostream>
#include <algorithm>
#include <vector>

struct Edge {
  int v1;
  int v2;
  int w;
};

bool comp(Edge& e1, Edge& e2) {
  return e1.w < e2.w;
}

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
  int n;
  std::cin >> n;
  std::vector<Edge> edges;
  for (int i = 0; i < n + 1; ++i) {
    for (int j = 0; j < n; ++j) {
      int w;
      std::cin >> w;
      if (w != 0) {
        edges.push_back(Edge{i, j, w});
      }
    }
  }

  sort(edges.begin(), edges.end(), comp);
  std::vector<int> parent(n + 1,-1); // parent[v] >= 0 - parent_node || parent[v] < 0 - -size of root
  int sum = 0;
  for (const Edge &e : edges) {
    if (join(e.v1, e.v2, parent)) {
      sum += e.w;
    }
  }
  std::cout << sum;
}