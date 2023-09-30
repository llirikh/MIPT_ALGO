#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> a(n), b(m);
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }

  std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));

  for (int i = 0; i < n; ++i) {
    int save = 0;
    for (int j = 0; j < m; ++j) {
      if (a[i] == b[j]) {
        dp[i][j] = save + 1;
      }
      if (i > 0) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j]);
      }
      if (b[j] < a[i]) {
        save = std::max(save, dp[i][j]);
      }
    }
  }

  int ans = 0;
  for (int j = 0; j < m; ++j) {
    ans = std::max(ans, dp[n - 1][j]);
  }

  std::cout << ans;
}