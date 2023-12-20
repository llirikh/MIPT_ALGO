#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  long double x;
  long double y;
};

struct SegmentPoint {
  long double x;
  bool is_begin;
};

void AddSegmentPoints(std::vector<SegmentPoint>& points, Point& point,
                      long double radius) {
  if (radius < std::abs(point.y)) {
    return;
  }
  auto discriminant = std::sqrt(radius * radius - point.y * point.y);
  points.emplace_back(point.x - discriminant, true);
  points.emplace_back(point.x + discriminant, false);
}

bool Comparator(SegmentPoint& lhs, SegmentPoint& rhs) {
  if (lhs.x == rhs.x) {
    if (lhs.is_begin == rhs.is_begin) {
      return false;
    }
    return lhs.is_begin;
  }
  return lhs.x < rhs.x;
}

bool IsCoverKPoints(std::vector<SegmentPoint>& points, size_t kk) {
  std::sort(points.begin(), points.end(), Comparator);

  size_t count = 0;
  for (auto& segment_point : points) {
    if (segment_point.is_begin) {
      ++count;
    } else {
      --count;
    }
    if (count >= kk) {
      return true;
    }
  }
  return false;
}

bool IsCoverKPoints(std::vector<Point>& points, long double radius, size_t kk) {
  std::vector<SegmentPoint> segment_points;
  for (auto& point : points) {
    AddSegmentPoints(segment_points, point, radius);
  }
  return IsCoverKPoints(segment_points, kk);
}

int main() {
  size_t number;
  size_t kk;
  std::cin >> number >> kk;
  std::vector<Point> points(number);
  for (size_t i = 0; i < number; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  const long double kLeft = 0;
  const long double kRight = 1e4;
  const long double kAccuracy = 1 / 1e5;

  long double left = kLeft;
  long double right = kRight;
  while (right - left > kAccuracy) {
    auto middle = left + (right - left) / 2;
    if (IsCoverKPoints(points, middle, kk)) {
      right = middle;
      continue;
    }
    left = middle;
  }

  const int kPrecision = 4;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  std::cout << right;
}