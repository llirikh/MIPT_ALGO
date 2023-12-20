#include <cmath>
#include <iomanip>
#include <iostream>

struct Point {
  long double x;
  long double y;
};

struct Segment {
  bool IsBelong(const Point& point) const;
  long double Length() const;

  Point a;
  Point b;
};

long double ScalarProduct(const Point& a1, const Point& a2, const Point& b1,
                          const Point& b2) {
  return (a2.x - a1.x) * (b2.x - b1.x) + (a2.y - a1.y) * (b2.y - b1.y);
}

bool Segment::IsBelong(const Point& point) const {
  static const long double kAccuracy = 0.0000001;
  bool is_line = std::abs(((b.x - a.x) * (point.y - a.y) -
                           (point.x - a.x) * (b.y - a.y))) <= kAccuracy;
  bool is_segment = ScalarProduct(point, a, point, b) <= kAccuracy;
  return is_line && is_segment;
}

long double Segment::Length() const {
  return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

struct Line {
  explicit Line(const Segment& segment);

  bool IsBelong(const Point& point) const;
  Segment NormalVector() const;

  long double a;
  long double b;
  long double c;
};

Line::Line(const Segment& segment) {
  a = segment.a.y - segment.b.y;
  b = segment.b.x - segment.a.x;
  c = -(segment.a.x * a + segment.a.y * b);
}

Segment Line::NormalVector() const {
  return Segment{{0, 0},
                 {a / std::sqrt(a * a + b * b), b / std::sqrt(a * a + b * b)}};
}

bool Line::IsBelong(const Point& point) const {
  static const long double kAccuracy = 0.0000001;
  return std::abs(a * point.x + b * point.y + c) <= kAccuracy;
}

bool IsParallel(const Line& lhs, const Line& rhs) {
  return lhs.a * rhs.b - rhs.a * lhs.b == 0;
}

Point Intersect(const Line& lhs, const Line& rhs) {
  Point intersect{};
  intersect.y =
      -(lhs.a * rhs.c - rhs.a * lhs.c) / (lhs.a * rhs.b - rhs.a * lhs.b);
  intersect.x =
      -(lhs.c * rhs.b - rhs.c * lhs.b) / (lhs.a * rhs.b - rhs.a * lhs.b);
  return intersect;
}

long double Distance(const Point& point, const Line& line) {
  return std::abs(line.a * point.x + line.b * point.y + line.c) /
         std::sqrt(line.a * line.a + line.b * line.b);
}

Point Projection(const Point& point, const Line& line) {
  auto result = point;
  auto dist = Distance(point, line);
  auto normal = line.NormalVector();
  normal.b.x *= dist;
  normal.b.y *= dist;

  result.x += normal.b.x;
  result.y += normal.b.y;
  if (line.IsBelong(result)) {
    return result;
  }

  result.x -= 2 * normal.b.x;
  result.y -= 2 * normal.b.y;
  return result;
}

long double Temp(const Point& point, const Segment& segment) {
  auto projection = Projection(point, Line(segment));
  if (segment.IsBelong(projection)) {
    return Segment{point, projection}.Length();
  }

  auto dist1 = Segment{point, segment.a}.Length();
  auto dist2 = Segment{point, segment.b}.Length();

  return std::min(dist1, dist2);
}

long double Distance(const Segment& segment1, const Segment& segment2) {
  Line line1(segment1);
  Line line2(segment2);

  if (!IsParallel(line1, line2)) {
    auto intersect = Intersect(line1, line2);
    if (segment1.IsBelong(intersect) && segment2.IsBelong(intersect)) {
      return 0;
    }
  }

  auto dist = Temp(segment1.a, segment2);
  dist = std::min(dist, Temp(segment1.b, segment2));
  dist = std::min(dist, Temp(segment2.a, segment1));
  dist = std::min(dist, Temp(segment2.b, segment1));

  return dist;
}

int main() {
  Segment segment1{};
  Segment segment2{};

  std::cin >> segment1.a.x >> segment1.a.y >> segment1.b.x >> segment1.b.y;
  std::cin >> segment2.a.x >> segment2.a.y >> segment2.b.x >> segment2.b.y;

  const int kPrecision = 6;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  std::cout << Distance(segment1, segment2);
}