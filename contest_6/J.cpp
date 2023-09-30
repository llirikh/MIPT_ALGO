#include <iostream>
#include <vector>

int main() {
  long long n;
  std::cin >> n;

  std::vector<long long> dp(n + 1, 0);
  std::vector<long long> accur(1e6 + 1, 0);

  if (n == 0) {
    std::cout << 0;
    return 0;
  }

  long long num;
  const long long kDivide = 1e9 + 7;
  for (long long i = 1; i < n + 1; ++i) {
    std::cin >> num;
    dp[i] = (2 * dp[i - 1]);
    if (accur[num] == 0) {
      dp[i] = (dp[i] + 1);
    } else {
      if (dp[i] - dp[accur[num] - 1] < 0) {
        dp[i] += 1e9 + 7;
      }
      dp[i] = (dp[i] - dp[accur[num] - 1]);
    }
    accur[num] = i;
    dp[i] %= kDivide;
  }

  std::cout << dp[n] % kDivide;
}