#include <algorithm>
#include <iostream>
#include <vector>

void Init(std::pair<int, int> p, std::vector<std::vector<int>>& dp,
          std::vector<std::vector<std::vector<int>>>& prev,
          std::vector<std::pair<int, std::string>>& man,
          std::vector<std::pair<int, std::string>>& girl) {
  int n = p.first;
  int m = p.second;
  dp[0][0] = 0;
  for (int i = 1; i < n + 1; ++i) {
    for (int j = 0; j < m + 1; ++j) {
      if (3 * i < j) {
        dp[i][j] = 1e9;
      } else {
        int mx = man[i - 1].first;
        if (j - 1 >= 0) {
          mx = std::max(mx, girl[j - 1].first);
        }
        if (i + j < 5) {
          dp[i][j] = mx;
        } else {
          if (i - 1 >= 0 && j - 3 >= 0 && dp[i][j] >= dp[i - 1][j - 3] + mx) {
            dp[i][j] = dp[i - 1][j - 3] + mx;
            prev[i][j][0] = i - 1;
            prev[i][j][1] = j - 3;
          }
          if (i - 2 >= 0 && j - 2 >= 0 && dp[i][j] >= dp[i - 2][j - 2] + mx) {
            dp[i][j] = dp[i - 2][j - 2] + mx;
            prev[i][j][0] = i - 2;
            prev[i][j][1] = j - 2;
          }
          if (i - 3 >= 0 && j - 1 >= 0 && dp[i][j] >= dp[i - 3][j - 1] + mx) {
            dp[i][j] = dp[i - 3][j - 1] + mx;
            prev[i][j][0] = i - 3;
            prev[i][j][1] = j - 1;
          }
          if (i - 4 >= 0 && dp[i][j] >= dp[i - 4][j] + mx) {
            dp[i][j] = dp[i - 4][j] + mx;
            prev[i][j][0] = i - 4;
            prev[i][j][1] = j;
          }
        }
      }
    }
  }
}

int main() {
  int n, m;
  std::cin >> n;
  std::vector<std::pair<int, std::string>> man(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> man[i].second >> man[i].first;
  }
  std::cin >> m;
  std::vector<std::pair<int, std::string>> girl(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> girl[i].second >> girl[i].first;
  }

  sort(girl.begin(), girl.end());
  sort(man.begin(), man.end());

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 1e9));
  std::vector<std::vector<std::vector<int>>> prev(
      n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(2, 0)));

  Init(std::pair<int, int>(n, m), dp, prev, man, girl);

  std::vector<std::vector<std::string>> ans;
  int i = n, j = m;
  while (i != 0 || j != 0) {
    ans.emplace_back();
    for (int k = prev[i][j][0] + 1; k <= i; ++k) {
      ans[ans.size() - 1].push_back(man[k - 1].second);
    }
    for (int k = prev[i][j][1] + 1; k <= j; ++k) {
      ans[ans.size() - 1].push_back(girl[k - 1].second);
    }
    int last_i = i;
    i = prev[i][j][0];
    j = prev[last_i][j][1];
  }

  std::cout << dp[n][m] << '\n';
  std::cout << ans.size() << '\n';
  for (int q = 0; q < (int)ans.size(); ++q) {
    std::cout << "Taxi " << q + 1 << ": ";
    for (int k = 0; k < (int)ans[q].size(); ++k) {
      if (k == 0) {
        std::cout << ans[q][k];
        if ((int)ans[q].size() == 1) {
          std::cout << '.';
        }
      } else {
        if (k == (int)ans[q].size() - 1) {
          std::cout << " and " << ans[q][k] << '.';
        } else {
          std::cout << ", " << ans[q][k];
        }
      }
    }
    std::cout << '\n';
  }
}