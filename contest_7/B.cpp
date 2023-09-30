// clang-format off
#include<iostream>
#include<vector>

const int kN = 100000;

std::vector<std::vector<int>> ans;
std::vector<std::vector<int>> g(kN);
std::vector<std::string> color(kN, "WHITE");

void Dfs(int v) {
  ans[ans.size() - 1].push_back(v);
  color[v] = "GREY";
  for (int to : g[v]) {
    if (color[to] != "WHITE") {
      continue;
    }
    Dfs(to);
  }
  color[v] = "BLACK";
}

int main() {
  int n, m;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    g[a - 1].push_back(b - 1);
    g[b - 1].push_back(a - 1);
  }
  for (int v = 0; v < n; ++v) {
    if (color[v] == "WHITE") {
      ans.emplace_back();
      Dfs(v);
    }
  }
  std::cout << ans.size() << '\n';
  for (auto vector : ans) {
    std::cout << vector.size() << '\n';
    for (auto item: vector) {
      std::cout << item + 1 << ' ';
    }
    std::cout << '\n';
  }
}
// clang-format on