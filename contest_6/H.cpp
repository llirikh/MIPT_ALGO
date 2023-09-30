#include <iostream>
#include <vector>

int main() {
  std::string s1, s2;
  std::cin >> s1 >> s2;
  int n = s1.length(), m = s2.length();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (int i = 1; i < n + 1; ++i) {
    for (int j = 1; j < m + 1; ++j) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  std::cout << dp[n][m] << '\n';

  int i = n, j = m;
  std::vector<int> ans1, ans2;
  while (dp[i][j] != 0) {
    if (s1[i - 1] == s2[j - 1]) {
      ans1.push_back(i);
      ans2.push_back(j);
      i -= 1;
      j -= 1;
    } else {
      if (dp[i - 1][j] > dp[i][j - 1]) {
        i -= 1;
      } else {
        j -= 1;
      }
    }
  }

  for (int k = ans1.size() - 1; k >= 0; --k) {
    std::cout << ans1[k] << ' ';
  }
  std::cout << '\n';
  for (int k = ans2.size() - 1; k >= 0; --k) {
    std::cout << ans2[k] << ' ';
  }
}