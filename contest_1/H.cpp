#include <cmath>
#include <iostream>

int a[900][3002];
int b[900][3002];

int F(int k, int i, int j) { return std::max(a[i][k], b[j][k]); }

int Search(int r, int l, int i, int j) {
  int ans = -1, mn = 1'000'000'000;
  for (int k = l; k <= r; k++) {
    if (F(k, i, j) <= mn) {
      ans = k;
      mn = F(k, i, j);
    }
  }
  return ans;
}

int TerSearch(int i, int j, int length) {
  int l = 0;
  int r = length;
  int m1, m2;
  while (true) {
    if (r - l <= 10) {
      return Search(r, l, i, j);
    }
    if (r - l > 10) {
      m1 = l + ceil((r - l) / 3.0);
      m2 = m1 + ceil((r - l) / 3.0);
      if (F(m1, i, j) > F(m2, i, j)) {
        l = m1;
      } else {
        r = m2;
      }
    }
  }
  return -1000;
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  int n, m, length;
  std::cin >> n >> m >> length;
  for (int i = 0; i < n; ++i) {
    a[i][0] = 10'000'000;
    for (int j = 1; j < length + 1; ++j) {
      std::cin >> a[i][j];
    }
    a[i][length + 1] = 10'000'000;
  }
  for (int i = 0; i < m; i++) {
    b[i][0] = 10'000'000;
    for (int j = 1; j < length + 1; j++) {
      std::cin >> b[i][j];
    }
    b[i][length + 1] = 10'000'000;
  }
  int q, i, j;
  std::cin >> q;
  for (int t = 0; t < q; t++) {
    std::cin >> i >> j;
    std::cout << TerSearch(i - 1, j - 1, length + 1) << '\n';
  }
  return 0;
}