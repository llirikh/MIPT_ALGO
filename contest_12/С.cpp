#include <iostream>
#include <numeric>
#include <vector>

int main() {
  const int kBigNumber = 1e9;
  int number;
  std::cin >> number;
  std::vector<int> array(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> array[i];
  }

  int cnt = 0;
  for (auto item : array) {
    if (item == 1) {
      ++cnt;
    }
  }
  if (cnt == number) {
    std::cout << 0;
    return 0;
  }
  if (cnt != 0) {
    std::cout << number - cnt;
    return 0;
  }

  int min = kBigNumber;
  for (int i = 0; i < number - 1; ++i) {
    int cur = array[i];
    for (int j = i; j < number; ++j) {
      cur = std::gcd(cur, array[j]);
      if (cur == 1) {
        min = std::min(min, number + j - i - 1);
        if (array[j] == 1) {
          min -= 1;
        }
        break;
      }
    }
  }
  if (min == kBigNumber) {
    std::cout << -1;
  } else {
    std::cout << min;
  }
}