#include <cmath>
#include <iostream>
#include <vector>

struct Point {
  long long x;
  long long y;
};

long long CrossProduct(Point& aa, Point& bb, Point& cc) {
  return (bb.x - aa.x) * (cc.y - aa.y) - (cc.x - aa.x) * (bb.y - aa.y);
}

int main() {
  int number;
  std::cin >> number;
  std::vector<Point> point(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> point[i].x >> point[i].y;
  }
  point.push_back(point[0]);
  point.push_back(point[1]);

  long long is_positive = 0;
  for (size_t i = 0; i < point.size() - 2; ++i) {
    if (CrossProduct(point[i], point[i + 1], point[i + 2]) == 0) {
      continue;
    }
    if (is_positive == 0) {
      is_positive = CrossProduct(point[i], point[i + 1], point[i + 2]);
    }
    if ((is_positive > 0) !=
        (CrossProduct(point[i], point[i + 1], point[i + 2]) > 0)) {
      std::cout << "NO";
      return 0;
    }
  }
  std::cout << "YES";
}