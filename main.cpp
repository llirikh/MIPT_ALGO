#include <iostream>
#include <vector>

int main() {
  std::string a_string, b_string;
  int number_of_changes;
  std::cin >> a_string >> b_string >> number_of_changes;
  
  int a_string_size = static_cast<int>(a_string.size());
  int b_string_size = static_cast<int>(b_string.size());

  
  if ((a_string_size - number_of_changes > b_string_size) || (a_string_size + number_of_changes < b_string_size)) {
    std::cout << -1;
    return 0;
  }

  int answer = 0;
  std::vector<std::vector<std::vector<int>>> dp(b_string_size + 1,
                                                std::vector<std::vector<int>>(number_of_changes + 1,std::vector<int>(number_of_changes + 1, 0)));
  for (int i = 1; i < b_string_size + 1; ++i) {
    for (int d = 0; d < number_of_changes + 1; ++d) {
      for (int a = 0; a < number_of_changes + 1 - d; ++a) {
        if ((i - a + d > 0) && (i - a + d <= a_string_size)) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i - 1][d][a] + static_cast<int>(a_string[i - a + d - 1] == b_string[i - 1]));
        }
        if (a > 0) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i - 1][d][a - 1] + 1);
        }
        if (d > 0) {
          dp[i][d][a] = std::max(dp[i][d][a], dp[i][d - 1][a]);
        }
        if ((i == b_string_size) && (a_string_size - d + a == b_string_size)) {
          int current = dp[i][d][a] + number_of_changes - a - d;
          current = std::min(current, i);
          answer = std::max(answer, current);
        }
      }
    }
  }

  std::cout << std::max(0, b_string_size - answer);

}