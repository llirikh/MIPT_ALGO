#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  std::vector<std::vector<int>> dp(2, std::vector<int>(n, 1));
  std::vector<std::vector<std::pair<int, int>>> prev(
      2, std::vector<std::pair<int, int>>(n, std::pair<int, int>(-1, -1)));

  for (int i = n - 1; i >= 0; --i) {
    std::cin >> a[i];
  }

  for (int j = 1; j < n; ++j) {
    for (int i = 0; i < 2; ++i) {
      if (dp[i][j - 1] > dp[i][j]) {
        dp[i][j] = dp[i][j - 1];
        prev[i][j].first = i;
        prev[i][j].second = j - 1;
      }
      for (int k = 0; k < j; ++k) {
        if (i == 0 && a[k] < a[j] && dp[1][k] + 1 >= dp[i][j]) {
          dp[i][j] = dp[1][k] + 1;
          prev[i][j].first = 1;
          prev[i][j].second = k;
        }
        if (i == 1 && a[k] > a[j] && dp[0][k] + 1 >= dp[i][j]) {
          dp[i][j] = dp[0][k] + 1;
          prev[i][j].first = 0;
          prev[i][j].second = k;
        }
      }
    }
  }

  int i = 0, j = n - 1;
  if (dp[1][j] > dp[0][j]) {
    i = 1;
  }

  std::cout << dp[i][j] << '\n';

  while (i != -1 && j != -1) {
    if (prev[i][j].first != i) {
      std::cout << a[j] << ' ';
    }
    int old_i = i;
    i = prev[i][j].first;
    j = prev[old_i][j].second;
  }
}