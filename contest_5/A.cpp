#include <iostream>
#include <vector>

const int kInf = -1'000'000'00;

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

int main() {
  SpeedUp();
  int n;
  std::cin >> n;
  std::vector<int> prev;
  std::vector<int> left;
  std::vector<int> right;
  std::vector<int> priority;
  int x, y;
  for (int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    if (i == 0) {
      prev.push_back(kInf);
      left.push_back(kInf);
      right.push_back(kInf);
    } else {
      if (priority[i - 1] < y) {
        prev.push_back(i - 1);
        left.push_back(kInf);
        right.push_back(kInf);
        right[i - 1] = i;
      } else {
        int ptr = i - 1;
        while (prev[ptr] != kInf && priority[ptr] > y) {
          ptr = prev[ptr];
        }
        if (prev[ptr] == kInf && priority[ptr] > y) {
          prev.push_back(kInf);
          left.push_back(ptr);
          right.push_back(kInf);
          prev[ptr] = i;
        } else {
          prev.push_back(ptr);
          left.push_back(right[ptr]);
          right.push_back(kInf);
          prev[right[ptr]] = i;
          right[ptr] = i;
        }
      }
    }
    priority.push_back(y);
  }
  std::cout << "YES" << '\n';
  for (int i = 0; i < n; ++i) {
    prev[i] == kInf ? std::cout << 0 << ' ' : std::cout << prev[i] + 1 << ' ';
    left[i] == kInf ? std::cout << 0 << ' ' : std::cout << left[i] + 1 << ' ';
    right[i] == kInf ? std::cout << 0 << ' ' : std::cout << right[i] + 1 << ' ';
    std::cout << '\n';
  }
}