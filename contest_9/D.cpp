#include <iostream>
#include <vector>

const int INF = 2e5;

int k_max = 20;
std::vector<std::vector<int>> lifts(k_max, std::vector<int>(INF, 0));

const int root = 0;
std::vector<std::vector<int>> g(INF);

std::vector<int> tin(INF, 0);
std::vector<int> tout(INF, 0);
std::vector<int> parent(INF, -1);
std::vector<int> dist(INF, 0);
std::vector<std::string> color(INF, "WHITE");


int timer = 0;

void Dfs(int v, int p) {
  for (int k = 0; k < k_max; ++k) {
    if (k == 0) {
      lifts[k][v] = p;
      if (p == -1) {
        lifts[k][v] = v;
      }
    } else {
      lifts[k][v] = lifts[k - 1][lifts[k - 1][v]];
    }
  }
  if (p == -1) {
    dist[v] = 0;
  } else {
    dist[v] = dist[p] + 1;
  }
  parent[v] = p;
  tin[v] = timer++;
  color[v] = "GREY";
  for (int to : g[v]) {
    if (color[to] != "WHITE") {
      continue;
    }
    Dfs(to, v);
  }
  tout[v] = timer++;
  color[v] = "BLACK";
}

bool ancestor(int x, int y) {
  return tin[x] <= tin[y] && tout[x] >= tout[y];
}

int lca(int u, int v) {
  if (ancestor(u, v)) {
    return u;
  }
  for (int k = k_max - 1; k >= 0; k--) {
    if (!ancestor(lifts[k][u], v)) {
      u = lifts[k][u];
    }
  }
  return lifts[0][u];
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    std::cin >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }

  Dfs(0, -1);

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int u, v, z;
    std::cin >> u >> v;
    --u;
    --v;
    z = lca(u, v);
    std::cout << dist[u] - dist[z] + dist[v] - dist[z] << '\n';
  }

}