#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

struct Point {
  long double x;
  long double y;
};

struct Segment {
  Point a;
  Point b;
};

struct Ray {
  Point a;
  Point b;
};

long double ScalarProduct(Point& a1, Point& a2, Point& b1, Point& b2) {
  return (a2.x - a1.x) * (b2.x - b1.x) + (a2.y - a1.y) * (b2.y - b1.y);
}

bool IsIntersect(Segment& segment, Ray& ray) {
  auto a1 = segment.a.y - segment.b.y;
  auto b1 = segment.b.x - segment.a.x;
  auto c1 = -(segment.a.x * a1 + segment.a.y * b1);
  auto a2 = ray.a.y - ray.b.y;
  auto b2 = ray.b.x - ray.a.x;
  auto c2 = -(ray.a.x * a2 + ray.a.y * b2);

  Point intersect{};
  intersect.y = (a2 * c1 - a1 * c2) / (a1 * b2 - a2 * b1);
  intersect.x = -(b2 * intersect.y + c2) / a2;

  auto in_segment =
      ScalarProduct(segment.a, intersect, segment.b, intersect) <= 0;
  auto in_ray = ScalarProduct(ray.a, ray.b, ray.a, intersect) >= 0;

  return in_segment && in_ray;
}

bool IsInSegment(Segment& seg, Point& point) {
  bool is_line = ((seg.b.x - seg.a.x) * (point.y - seg.a.y) -
                  (point.x - seg.a.x) * (seg.b.y - seg.a.y)) == 0;
  bool is_segment = ScalarProduct(point, seg.a, point, seg.b) <= 0;
  return is_line && is_segment;
}

int main() {
  int number;
  Point main{};
  std::cin >> number >> main.x >> main.y;
  std::vector<Segment> segment(number);
  for (int i = 0; i < number; ++i) {
    Point point{};
    std::cin >> point.x >> point.y;
    segment[i].a = point;
    segment[(i - 1 + number) % number].b = point;
  }
  const int kBigNumber = 1000;
  srand(time(nullptr));
  Ray ray1(main, {static_cast<long double>(random() % kBigNumber) / 2,
                  static_cast<long double>(random() % kBigNumber) / 2});
  Ray ray2(main, {static_cast<long double>(random() % kBigNumber) / 2,
                  static_cast<long double>(random() % kBigNumber) / 2});

  int count = 0;
  for (auto& seg : segment) {
    if (IsInSegment(seg, main)) {
      std::cout << "YES";
      return 0;
    }
    auto cnt1 = static_cast<int>(IsIntersect(seg, ray1));
    auto cnt2 = static_cast<int>(IsIntersect(seg, ray2));
    count += std::min(cnt1, cnt2);
  }

  if (count % 2 == 1) {
    std::cout << "YES";
    return 0;
  }
  std::cout << "NO";
}