#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  long double x;
  long double y;
};

int main() {
  Point point_a{};
  Point point_b{};
  Point point_c{};

  std::cin >> point_c.x >> point_c.y;
  std::cin >> point_a.x >> point_a.y;
  std::cin >> point_b.x >> point_b.y;

  long double aa = point_b.y - point_a.y;
  long double bb = point_a.x - point_b.x;
  long double cc = -(aa * point_a.x + point_a.y * (point_a.x - point_b.x));

  long double d1 = std::abs(aa * point_c.x + bb * point_c.y + cc) /
                   std::sqrt(aa * aa + bb * bb);

  long double d2 = d1;
  if ((point_c.x - point_a.x) * (point_b.x - point_a.x) +
          (point_c.y - point_a.y) * (point_b.y - point_a.y) <
      0) {
    d2 = std::sqrt((point_a.x - point_c.x) * (point_a.x - point_c.x) +
                   (point_a.y - point_c.y) * (point_a.y - point_c.y));
  }

  long double d3 = d1;
  if ((point_c.x - point_a.x) * (point_b.x - point_a.x) +
              (point_c.y - point_a.y) * (point_b.y - point_a.y) <
          0 ||
      (point_c.x - point_b.x) * (point_a.x - point_b.x) +
              (point_c.y - point_b.y) * (point_a.y - point_b.y) <
          0) {
    auto dd1 = std::sqrt((point_a.x - point_c.x) * (point_a.x - point_c.x) +
                         (point_a.y - point_c.y) * (point_a.y - point_c.y));
    auto dd2 = std::sqrt((point_b.x - point_c.x) * (point_b.x - point_c.x) +
                         (point_b.y - point_c.y) * (point_b.y - point_c.y));
    d3 = std::min(dd1, dd2);
  }

  const int kPrecision = 6;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  std::cout << d1 << '\n' << d2 << '\n' << d3 << '\n';
}