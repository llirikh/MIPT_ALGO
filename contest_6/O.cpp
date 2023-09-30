#include <iostream>
#include <vector>

bool Bit(int i, int mask) { return ((mask >> i) & 1) != 0; }

int Count(int mask) {
  int count = 0;
  for (; mask != 0; mask >>= 1) {
    count += mask & 1;
  }
  return count;
}

void Out(int n, std::vector<std::vector<int>>& dp,
         std::vector<std::vector<std::vector<int>>>& prev) {
  int size = (1 << n), inf = 1e9;
  int ans = inf, idx = -1;
  for (int i = 0; i < n; ++i) {
    if (ans >= dp[size - 1][i]) {
      ans = dp[size - 1][i];
      idx = i;
    }
  }
  std::cout << ans << '\n';
  std::cout << idx + 1 << ' ';

  int mask = size - 1, i = idx;
  while (mask != -1 || i != -1) {
    if (prev[mask][i][1] != -1) {
      std::cout << prev[mask][i][1] + 1 << ' ';
    }
    int old_mask = mask;
    mask = prev[mask][i][0];
    i = prev[old_mask][i][1];
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> d(n, std::vector<int>(n, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cin >> d[i][j];
    }
  }

  int size = (1 << n), inf = 1e9;
  std::vector<std::vector<int>> dp(size, std::vector<int>(n, inf));
  std::vector<std::vector<std::vector<int>>> prev(
      size, std::vector<std::vector<int>>(n, std::vector<int>(2, -1)));
  for (int mask = 0; mask < size; ++mask) {
    for (int i = 0; i < n; ++i) {
      if (Count(mask) == 1 && Bit(i, mask)) {
        dp[mask][i] = 0;
      } else {
        if (Count(mask) > 1 && Bit(i, mask)) {
          for (int j = 0; j < n; ++j) {
            if (Bit(j, mask) &&
                dp[mask][i] >= dp[mask ^ (1 << i)][j] + d[i][j]) {
              dp[mask][i] = dp[mask ^ (1 << i)][j] + d[i][j];
              prev[mask][i][0] = mask ^ (1 << i);
              prev[mask][i][1] = j;
            }
          }
        }
      }
    }
  }

  Out(n, dp, prev);

  return 0;
}