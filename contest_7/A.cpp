// clang-format off
#include<iostream>
#include<vector>
#include<deque>
#include<cstdlib>

const int kN = 100000;

std::vector<std::vector<int>> g(kN);
std::vector<std::string> color(kN, "WHITE");
std::vector<int> parent(kN, -5);

void PrintCycle(int cur, int last) {
  std::cout << "YES" << '\n';
  std::deque<int> ans;
  while (cur != last) {
    ans.push_front(cur + 1);
    cur = parent[cur];
  }
  ans.push_front(last + 1);
  for (int item : ans) {
    std::cout << item << ' ';
  }
}

void Dfs(int v, int p) {
  parent[v] = p;
  color[v] = "GREY";
  for (int to : g[v]) {
    if (color[to] == "BLACK") {
      continue;
    }
    if (color[to] == "GREY") {
      PrintCycle(v, to);
      exit(EXIT_SUCCESS);
    }
    if (color[to] != "WHITE") {
      continue;
    }
    Dfs(to, v);
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
  }
  for (int v = 0; v < n; ++v) {
    if (color[v] == "WHITE") {
      Dfs(v, -1);
    }
  }
  std::cout << "NO";
}
// clang-format on