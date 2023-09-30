// clang-format off
#include<iostream>
#include<vector>
#include<set>
#include<map>

const int kN = 20000;

std::set<std::pair<int, int>> bridges;

std::vector<std::vector<int>> g(kN);
std::vector<int> tin(kN, -1);
int timer = 0;
std::vector<bool> used(kN, false);
std::vector<int> ret(kN);

void Dfs(int v, int p) {
  tin[v] = timer++;
  ret[v] = tin[v];
  used[v] = true;
  for (int to : g[v]) {
    if (to == p) {
      continue;
    }
    if (used[to]) {
      ret[v] = std::min(ret[v], tin[to]);
    } else {
      Dfs(to, v);
      if (ret[to] >= tin[to]) {
        bridges.insert(std::pair<int, int>(v, to));
        bridges.insert(std::pair<int, int>(to, v));
      }
      ret[v] = std::min(ret[v], ret[to]);
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> edge;

  std::map<std::pair<int, int>, int> check;

  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
    edge.emplace_back(a - 1, b - 1);
    std::pair<int, int> pair(a - 1, b - 1);
    std::pair<int, int> pair_r(b - 1, a - 1);
    if (check.find(pair) == check.end() && check.find(pair_r) == check.end()) {
      check.insert({pair, 1});
      check.insert({pair_r, 1});
    } else {
      check[pair] += 1;
      check[pair_r] += 1;
    }
  }
  for (int v = 0; v < n; ++v) {
    if (!used[v]) {
      Dfs(v, -1);
    }
  }

  for (auto i = bridges.begin(); i != bridges.end(); ++i) {
    if (check[*i] != 1) {
      bridges.erase(i);
    }
  }
  std::cout << bridges.size() / 2 << '\n';
  for (int i = 0; i < m; ++i) {
    if (bridges.find(edge[i]) != bridges.end() && check[edge[i]] == 1) {
      std::cout << i + 1 << ' ';
    }
  }
}
// clang-format on