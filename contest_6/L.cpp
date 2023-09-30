#include <iostream>
#include <vector>

int main() {
  int n, g, s;
  std::cin >> n >> g >> s;

  std::vector<std::vector<int>> k(g), w(g);
  for (int i = 0; i < n; ++i) {
    int cur_k, cur_w, cur_g;
    std::cin >> cur_k >> cur_w >> cur_g;
    k[cur_g - 1].push_back(cur_k);
    w[cur_g - 1].push_back(cur_w);
  }

  std::vector<std::vector<int>> dp(g + 1, std::vector<int>(s + 1, 0));
  for (int i = 1; i < g + 1; ++i) {
    for (int j = 1; j < s + 1; ++j) {
      dp[i][j] = dp[i - 1][j];
      for (int q = 0; q < (int)k[i - 1].size(); ++q) {
        if (j - k[i - 1][q] >= 0) {
          dp[i][j] =
              std::max(dp[i][j], dp[i - 1][j - k[i - 1][q]] + w[i - 1][q]);
        }
      }
    }
  }

  std::cout << dp[g][s];
}