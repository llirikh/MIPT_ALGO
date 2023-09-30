// // clang-format off
#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<cstdlib>

const int kN = 100000;

std::vector<std::vector<int>> g(kN);
std::vector<std::vector<int>> gr(kN);
std::vector<int> tin(kN, -1);
std::vector<std::vector<int>> tout(kN, std::vector<int>(2));
int timer = 0;
std::vector<std::string> color(kN, "WHITE");
std::vector<int> new_v(kN);
std::vector<std::vector<int>> ans;

void DfsR(int v) {
  ans[ans.size() - 1].push_back(v);
  color[v] = "GREY";
  for (int to : gr[v]) {
    if (color[to] != "WHITE") {
      continue;
    }
    DfsR(to);
  }
  color[v] = "BLACK";
}

void Dfs(int v) {
  tin[v] = timer++;
  color[v] = "GREY";
  for (int to : g[v]) {
    if (color[to] != "WHITE") {
      continue;
    }
    Dfs(to);
  }
  tout[v][0] = timer++;
  color[v] = "BLACK";
}

int main() {
  int n, m;
  std::cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    g[a - 1].push_back(b - 1);
    gr[b - 1].push_back(a - 1);
  }
  for (int v = 0; v < n; ++v) {
    tout[v][1] = v;
    if (color[v] == "WHITE") {
      Dfs(v);
    }
  }
  std::sort(tout.begin(), tout.begin() + n);
  for (int i = n - 1; i >= 0 ; --i) {
    new_v[n - 1 - i] = tout[i][1];
    color[i] = "WHITE";
  }

  for (int v: new_v) {
    if (color[v] == "WHITE") {
      ans.emplace_back();
      DfsR(v);
    }
  }

  for (auto vector : ans) {
    for (int item : vector) {
      std::cout << item << ' ';
    }
    std::cout << '\n';
  }



}
// clang-format on