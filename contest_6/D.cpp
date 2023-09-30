#include <iostream>
#include <vector>

int main() {
  int max_height, number_of_planes;
  std::cin >> max_height >> number_of_planes;

  std::vector<std::vector<int>> dp(max_height + 1, std::vector<int>());

  if (number_of_planes == 0 && max_height == 1) {
    std::cout << 0;
    return 0;
  }

  if (number_of_planes == 0 && max_height > 1) {
    std::cout << -1;
    return 0;
  }

  for (int j = 0; j < max_height + 1; ++j) {
    for (int i = 0; i < number_of_planes + 1; ++i) {
      if (i == 0 || j == 0) {
        dp[i].push_back(1);
      } else {
        if (i == 1) {
          dp[i].push_back(j + 1);
        } else {
          dp[i].push_back(dp[i - 1][j - 1] + dp[i][j - 1]);
        }
      }
      if (dp[i][j] >= max_height) {
        std::cout << j;
        return 0;
      }
    }
  }
}