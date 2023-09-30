#include <iostream>
#include <vector>

int main() {
  int number, money;
  std::cin >> number >> money;
  std::vector<int> cost(number), prize(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> cost[i];
  }
  for (int i = 0; i < number; ++i) {
    std::cin >> prize[i];
  }

  std::vector<std::vector<int>> max_prize(number + 1,
                                          std::vector<int>(money + 1, 0));
  for (int i = 1; i < number + 1; ++i) {
    for (int j = 1; j < money + 1; ++j) {
      if (j - cost[i - 1] >= 0) {
        max_prize[i][j] = max_prize[i - 1][j - cost[i - 1]] + prize[i - 1];
      }
      max_prize[i][j] = std::max(max_prize[i][j], max_prize[i - 1][j]);
    }
  }

  int i = number, j = money;
  while (max_prize[i][j] != 0) {
    if (j - cost[i - 1] >= 0 &&
        max_prize[i - 1][j - cost[i - 1]] + prize[i - 1] == max_prize[i][j]) {
      std::cout << i << '\n';
      j -= cost[i - 1];
    }
    i -= 1;
  }
}