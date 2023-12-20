#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

static const long double kAccuracy = 0.0000001;

struct Point {
  long double x;
  long double y;
};

struct Segment {
  long double Length() const;
  bool IsBelong(const Point& point) const;
  void Normalize();
  Segment Perpendicular() const;

  Point a;
  Point b;
};

struct Line {
  Line() = default;
  explicit Line(const Segment& segment);

  bool IsBelong(const Point& point) const;
  Point Projection(const Point& point) const;
  Segment NormalVector() const;

  long double a;
  long double b;
  long double c;
};

struct Circle {
  Point center;
  long double radius;
};

long double ScalarProduct(const Point& a1, const Point& a2, const Point& b1,
                          const Point& b2) {
  return (a2.x - a1.x) * (b2.x - b1.x) + (a2.y - a1.y) * (b2.y - b1.y);
}

long double Segment::Length() const {
  return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

bool Segment::IsBelong(const Point& point) const {
  bool is_line = std::abs(((b.x - a.x) * (point.y - a.y) -
                           (point.x - a.x) * (b.y - a.y))) <= kAccuracy;
  bool is_segment = ScalarProduct(point, a, point, b) <= kAccuracy;
  return is_line && is_segment;
}

void Segment::Normalize() {
  auto length = Length();

  b.x -= a.x;
  b.y -= a.y;
  a.x = 0;
  a.y = 0;

  if (length <= kAccuracy) {
    return;
  }

  b.x /= length;
  b.y /= length;
}

Segment Segment::Perpendicular() const { return {a, {b.y, -b.x}}; }

long double Distance(const Point& point, const Line& line) {
  return std::abs(line.a * point.x + line.b * point.y + line.c) /
         std::sqrt(line.a * line.a + line.b * line.b);
}

Line::Line(const Segment& segment) {
  a = segment.a.y - segment.b.y;
  b = segment.b.x - segment.a.x;
  c = -(segment.a.x * a + segment.a.y * b);
}

bool Line::IsBelong(const Point& point) const {
  return std::abs(a * point.x + b * point.y + c) <= kAccuracy;
}

Segment Line::NormalVector() const {
  return Segment{{0, 0},
                 {a / std::sqrt(a * a + b * b), b / std::sqrt(a * a + b * b)}};
}

Point Line::Projection(const Point& point) const {
  auto result = point;
  auto dist = Distance(point, *this);
  auto normal = NormalVector();
  normal.b.x *= dist;
  normal.b.y *= dist;

  result.x += normal.b.x;
  result.y += normal.b.y;
  if (IsBelong(result)) {
    return result;
  }

  result.x -= 2 * normal.b.x;
  result.y -= 2 * normal.b.y;
  return result;
}

std::vector<Point> Intersect(const Circle& circle, const Line& line) {
  std::vector<Point> points;

  auto projection = line.Projection(circle.center);
  Segment height{circle.center, projection};
  auto distance = height.Length();

  if (distance - circle.radius > kAccuracy) {
    return points;
  }

  if (distance <= kAccuracy) {
    height = line.NormalVector();
  }
  height.Normalize();
  auto direction = height.Perpendicular();
  auto multiplier =
      std::sqrt(circle.radius * circle.radius - distance * distance);
  direction.b.x *= multiplier;
  direction.b.y *= multiplier;

  auto point1 = projection;
  point1.x += direction.b.x;
  point1.y += direction.b.y;
  points.push_back(point1);

  if (std::abs(circle.radius - distance) <= kAccuracy) {
    return points;
  }

  auto point2 = projection;
  point2.x -= direction.b.x;
  point2.y -= direction.b.y;
  points.push_back(point2);

  return points;
}

long double ArcLength(const Point& point1, const Point& point2,
                      const Circle& circle) {
  Segment circle_path{point1, point2};
  auto circle_length = circle_path.Length();
  auto arc_length = std::acos(1 - (circle_length * circle_length) /
                                      (2 * circle.radius * circle.radius)) *
                    circle.radius;
  return arc_length;
}

std::vector<Point> ContactPoints(const Point& point, const Circle& circle) {
  auto x0 = point.x - circle.center.x;
  auto y0 = point.y - circle.center.y;

  auto dd = std::sqrt(x0 * x0 + y0 * y0);
  auto aa = std::pow(circle.radius, 2) / (dd * dd);
  auto bb = circle.radius * std::sqrt(dd * dd - std::pow(circle.radius, 2)) /
            (dd * dd);

  std::vector<Point> points;

  Point point1{};
  point1.x = aa * x0 + bb * (-y0) + circle.center.x;
  point1.y = aa * y0 + bb * x0 + circle.center.y;
  points.push_back(point1);

  if (bb == 0) {
    return points;
  }

  Point point2{};
  point2.x = aa * x0 - bb * (-y0) + circle.center.x;
  point2.y = aa * y0 - bb * x0 + circle.center.y;
  points.push_back(point2);

  return points;
}

int main() {
  Point point1{};
  Point point2{};
  Circle circle{};

  std::cin >> point1.x >> point1.y >> point2.x >> point2.y;
  std::cin >> circle.center.x >> circle.center.y >> circle.radius;

  const int kPrecision = 6;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);

  auto points = Intersect(circle, Line({point1, point2}));

  Segment direct_path{point1, point2};
  auto direct_length = direct_path.Length();

  if (points.size() < 2) {
    std::cout << direct_length;
    return 0;
  }

  if (!direct_path.IsBelong(points[0]) || !direct_path.IsBelong(points[1])) {
    std::cout << direct_length;
    return 0;
  }

  auto points1 = ContactPoints(point1, circle);
  auto points2 = ContactPoints(point2, circle);

  const long double kBigNumber = 1e9;
  long double dist = kBigNumber;
  for (auto contact_point1 : points1) {
    for (auto contact_point2 : points2) {
      Segment segment1{point1, contact_point1};
      Segment segment2{point2, contact_point2};
      auto new_dist = segment1.Length() + segment2.Length() +
                      ArcLength(contact_point1, contact_point2, circle);
      dist = std::min(dist, new_dist);
    }
  }

  std::cout << dist;
  return 0;
}