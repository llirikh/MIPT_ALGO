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