#include <iostream>
#include <vector>

int m, n, a, b;
std::vector<bool> used(10000, false);
std::vector<int> match(10000, -1);
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

bool correct(int x, int y) {
  return (x >= 0 && y >= 0 && x < m && y < n);
}

int main() {
  std::cin >> m >> n >> a >> b;
  std::vector<std::string> board(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> board[i];
  }

  int x, y, count = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      g.emplace_back();
      if (board[i][j] == '.') {
        continue;
      }
      ++count;
      if ((i + j) % 2 == 0) {
        x = i - 1;
        y = j;
        if (correct(x, y) && board[x][y] != '.') {
          g[i * n + j].push_back(x * n + y);
        }
        x = i + 1;
        y = j;
        if (correct(x, y) && board[x][y] != '.') {
          g[i * n + j].push_back(x * n + y);
        }
        x = i;
        y = j - 1;
        if (correct(x, y) && board[x][y] != '.') {
          g[i * n + j].push_back(x * n + y);
        }
        x = i;
        y = j + 1;
        if (correct(x, y) && board[x][y] != '.') {
          g[i * n + j].push_back(x * n + y);
        }
      }
    }
  }

  if (2*b < a) {
    std::cout << count * b;
    return 0;
  }

  used.assign(10000, false);
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if ((i + j) % 2 == 0) {
        int v = i * n + j;
        if (augment(v)) {
          used.assign(10000, false);
        }
      }
    }
  }

  int count_dom = 0;
  for (int i = 0; i < m * n; ++i) {
    if (match[i] != -1) {
      ++count_dom;
    }
  }

  std::cout << count_dom * a + (count - count_dom * 2) * b << '\n';
}