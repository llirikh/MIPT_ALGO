#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

int Sum(int i, int j, std::vector<int>& pref) {
  if (j < i) {
    return 0;
  }
  return pref[j + 1] - pref[i];
}

void InitDIff(std::vector<int>& c, std::vector<std::vector<int>>& diff,
              std::vector<int> pref, int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int m = ceil((c[i] + c[j]) / 2.0);
      int i_m = std::lower_bound(c.begin(), c.end(), m) - c.begin();
      diff[i][j] += (n - i_m) * c[i] - Sum(i_m, n - 1, pref);
      diff[i][j] += (j - i_m) * c[j] - Sum(i_m, j - 1, pref);
      diff[i][j] += Sum(j + 1, n - 1, pref) - (n - j - 1) * c[j];
    }
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int> c(n);
  std::vector<int> pref(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    std::cin >> c[i];
    pref[i + 1] = pref[i] + c[i];
  }

  std::vector<std::vector<int>> diff(n, std::vector<int>(n, 0));
  InitDIff(c, diff, pref, n);

  std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
  std::vector<std::vector<int>> ans(m, std::vector<int>(n, -1));
  for (int j = 0; j < n; ++j) {
    dp[0][j] =
        Sum(j + 1, n - 1, pref) - Sum(0, j - 1, pref) + (2 * j - n + 1) * c[j];
  }
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j < i) {
        ans[i][j] = j - 1;
        dp[i][j] = dp[i - 1][j];
        continue;
      }
      int min = 1e7;
      for (int k = i - 1; k < j; ++k) {
        if (dp[i - 1][k] + diff[k][j] <= min) {
          min = dp[i - 1][k] + diff[k][j];
          ans[i][j] = k;
        }
      }
      dp[i][j] = min;
    }
  }

  int i_ans = m - 1, j_ans = n - 1;
  int min = 1e7;
  for (int j = 0; j < n; ++j) {
    if (dp[i_ans][j] < min) {
      min = dp[i_ans][j];
      j_ans = j;
    }
  }

  std::cout << dp[i_ans][j_ans] << '\n';
  std::vector<int> out;
  out.push_back(c[j_ans]);
  while (i_ans > 0) {
    out.push_back(c[ans[i_ans][j_ans]]);
    j_ans = ans[i_ans][j_ans];
    i_ans -= 1;
  }

  for (int i = out.size() - 1; i >= 0; --i) {
    std::cout << out[i] << ' ';
  }
}