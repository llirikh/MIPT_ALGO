#include <iostream>
#include <vector>

//TODO Разбить по функциям

std::vector<bool> used(2000, false);
std::vector<int> match(2000, -1);
std::vector<std::vector<int>> g(1000);

bool augment(int v) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  for (int to : g[v]) {
    if (match[to] == -1 || augment(match[to])) {
      match[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int from, to;
    std::cin >> from >> to;
    g[from - 1].push_back(to + n - 1);
  }

//  for (int i = 0; i < g.size(); ++i) {
//    std::cout << i << ": ";
//    for (int item : g[i]) {
//      std::cout << item << ' ';
//    }
//    std::cout << '\n';
//  }

  used.assign(2000, false);
  for (int v = 0; v < n; ++v) {
    if (augment(v)) {
      used.assign(2000, false);
    }
  }

  int count = 0;
  for (int item : match) {
    if (item != -1) {
      ++count;
    }
  }


  std::cout << n - count;

}