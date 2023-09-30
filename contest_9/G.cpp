#include <iostream>
#include <vector>

std::vector<bool> used(501, false);
std::vector<int> match(501, -1);
std::vector<std::vector<int>> g;

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
  int l, r;
  std::cin >> l >> r;
  for (int i = 0; i < l; ++i) {
    g.emplace_back();
    int to = -1;
    while (to != 0) {
      std::cin >> to;
      if (to != 0) {
        g[i].push_back(to + l - 1);
      }
    }
  }

  used.assign(501, false);
  for (int v = 0; v < l; ++v) {
    if (augment(v)) {
      used.assign(501, false);
    }
  }

  int count = 0;
  for (int i = l; i < l + r; ++i) {
    if (match[i] != -1) {
      ++count;
    }
  }

  std::cout << count << '\n';
  for (int i = l; i < l + r; ++i) {
    if (match[i] != -1) {
      std::cout << match[i] + 1 << ' ' << i + 1 - l<< '\n';
    }
  }

}