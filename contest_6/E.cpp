#include <iostream>
#include <vector>

int main() {
  long long n;
  std::cin >> n;
  std::vector<std::vector<long long>> dp(n + 1,
                                         std::vector<long long>(n + 1, 0));
  for (long long i = 0; i < n + 1; ++i) {
    dp[0][i] = 1;
  }

  for (long long i = 1; i < n + 1; ++i) {
    for (long long j = 1; j < n + 1; ++j) {
      dp[i][j] += dp[i][j - 1];
      if (j <= i) {
        dp[i][j] += dp[i - j][j / 2];
      }
    }
  }

  std::cout << dp[n][n];
}