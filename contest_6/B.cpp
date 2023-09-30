#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int number;
  std::cin >> number;

  std::vector<long long> sequence(number);
  std::vector<long long> dp(number, 2147483647);
  std::vector<int> position(number, -1);
  std::vector<int> previous(number, -1);

  int max_position = -1;
  for (int i = 0; i < number; ++i) {
    std::cin >> sequence[i];
    int j = std::lower_bound(dp.begin(), dp.end(), -sequence[i]) - dp.begin();
    dp[j] = -sequence[i];
    position[j] = i;
    max_position = std::max(max_position, j);
    if (j != 0) {
      previous[i] = position[j - 1];
    }
  }

  std::cout << max_position + 1 << '\n';

  std::vector<long long> answer;

  int index = position[max_position];
  while (index != -1) {
    answer.push_back(index);
    index = previous[index];
  }

  for (int i = answer.size() - 1; i >= 0; --i) {
    std::cout << answer[i] + 1 << ' ';
  }
}