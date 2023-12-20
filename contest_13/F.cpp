#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  long double x;
  long double y;
};

struct Line {
  long double a;
  long double b;
  long double c;
};

struct Circle {
  Point center;
  long double radius;
};

Point Intersect(Line& lhs, Line& rhs) {
  Point intersect{};
  intersect.y =
      -(lhs.a * rhs.c - rhs.a * lhs.c) / (lhs.a * rhs.b - rhs.a * lhs.b);
  intersect.x =
      -(lhs.c * rhs.b - rhs.c * lhs.b) / (lhs.a * rhs.b - rhs.a * lhs.b);
  return intersect;
}

Line Tangent(Circle& circle1, Circle& circle2) {
  Line line{};

  auto dr = circle2.radius - circle1.radius;
  auto dx = circle2.center.x - circle1.center.x;
  auto dy = circle2.center.y - circle1.center.y;
  auto dd = std::sqrt(dx * dx + dy * dy);
  auto rr = dr / dd;
  auto xx = dx / dd;
  auto yy = dy / dd;

  line.a = rr * xx - yy * std::sqrt(1 - rr * rr);
  line.b = rr * yy + xx * std::sqrt(1 - rr * rr);
  line.c =
      circle1.radius - (line.a * circle1.center.x + line.b * circle1.center.y);

  return line;
}

int main() {
  Circle circle1{};
  Circle circle2{};

  std::cin >> circle1.radius >> circle1.center.y;
  std::cin >> circle2.radius >> circle2.center.y;

  auto line = Tangent(circle1, circle2);

  Line abscissa{0, 1, 0};
  auto limit = Intersect(abscissa, line).x;

  const int kPrecision = 6;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  std::cout << std::max(static_cast<long double>(0), limit);
}