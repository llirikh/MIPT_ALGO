#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  Point operator+(const Point& point) const;
  Point operator-(const Point& point) const;
  Point& operator*=(long double number);

  long double Length() const;

  long double x;
  long double y;
};

Point Point::operator+(const Point& point) const {
  return {x + point.x, y + point.y};
}

Point Point::operator-(const Point& point) const {
  return {x - point.x, y - point.y};
}

Point& Point::operator*=(long double number) {
  x *= number;
  y *= number;
  return *this;
}

long double Point::Length() const { return std::sqrt(x * x + y * y); }

void ReorderByY(std::vector<Point>& polygon) {
  int idx = 0;
  for (int i = 1; i < static_cast<int>(polygon.size()); ++i) {
    if (polygon[i].y < polygon[idx].y) {
      idx = i;
      continue;
    }
    if (polygon[i].y == polygon[idx].y && polygon[i].x < polygon[idx].x) {
      idx = i;
    }
  }

  std::rotate(polygon.begin(), polygon.begin() + idx, polygon.end());
}

void ReorderByX(std::vector<Point>& polygon) {
  int idx = 0;
  for (int i = 1; i < static_cast<int>(polygon.size()); ++i) {
    if (polygon[i].x < polygon[idx].x) {
      idx = i;
      continue;
    }
    if (polygon[i].x == polygon[idx].x && polygon[i].y < polygon[idx].y) {
      idx = i;
    }
  }

  std::rotate(polygon.begin(), polygon.begin() + idx, polygon.end());
}

long double Scalar(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double CosAngle(const Point& lhs, const Point& rhs) {
  return Scalar(lhs, rhs) / (lhs.Length() * rhs.Length());
}

std::vector<Point> Sum(std::vector<Point>& polygon1,
                       std::vector<Point>& polygon2) {
  ReorderByY(polygon1);
  ReorderByY(polygon2);

  polygon1.push_back(polygon1[0]);
  polygon2.push_back(polygon2[0]);

  std::vector<Point> sum = {polygon1[0] + polygon2[0]};
  size_t i1 = 0;
  size_t i2 = 0;
  if (CosAngle(polygon1[1] - polygon1[0], {1, 0}) >
      CosAngle(polygon2[1] - polygon2[0], {1, 0})) {
    ++i1;
  } else {
    ++i2;
  }

  while (i1 < polygon1.size() - 1 || i2 < polygon2.size() - 1) {
    sum.push_back(polygon1[i1] + polygon2[i2]);

    if (i1 == polygon1.size() - 1) {
      ++i2;
      continue;
    }

    if (i2 == polygon2.size() - 1) {
      ++i1;
      continue;
    }

    auto vector1 = polygon1[i1 + 1] - polygon1[i1];
    auto vector2 = polygon2[i2 + 1] - polygon2[i2];
    auto vector = sum[sum.size() - 1] - sum[sum.size() - 2];

    if (CosAngle(vector, vector1) > CosAngle(vector, vector2)) {
      if (i1 < polygon1.size() - 1) {
        ++i1;
      }
    } else {
      if (i2 < polygon2.size() - 1) {
        ++i2;
      }
    }
  }

  polygon1.pop_back();
  polygon2.pop_back();

  return sum;
}

static const long double kAccuracy = 1 / 1e8;

bool IsOnOneLine(const Point& point1, const Point& point2,
                 const Point& point3) {
  auto value1 = (point3.x - point1.x) * (point2.y - point1.y);
  auto value2 = (point3.y - point1.y) * (point2.x - point1.x);
  return std::abs(value1 - value2) <= kAccuracy;
}

std::vector<Point> Clear(const std::vector<Point>& polygon) {
  std::vector<Point> new_polygon;
  const size_t kMinSize = 2;
  for (const auto& point : polygon) {
    while (new_polygon.size() >= kMinSize &&
           IsOnOneLine(new_polygon[new_polygon.size() - 1],
                       new_polygon[new_polygon.size() - 2], point)) {
      new_polygon.pop_back();
    }
    new_polygon.push_back(point);
  }

  auto point = new_polygon[0];
  while (new_polygon.size() > kMinSize &&
         IsOnOneLine(new_polygon[new_polygon.size() - 1],
                     new_polygon[new_polygon.size() - 2], point)) {
    new_polygon.pop_back();
  }

  ReorderByX(new_polygon);
  return new_polygon;
}

long double Rotate(const Point& point_a, const Point& point_b,
                   const Point& point_c) {
  return (point_b.x - point_a.x) * (point_c.y - point_b.y) -
         (point_b.y - point_a.y) * (point_c.x - point_b.x);
}

bool IsIntersected(const Point& point1, const Point& point2,
                   const Point& point3, const Point& point4) {
  return Rotate(point1, point2, point3) * Rotate(point1, point2, point4) <= 0 &&
         Rotate(point3, point4, point1) * Rotate(point3, point4, point2) < 0;
}

bool IsLocated(const std::vector<Point>& polygon, const Point& point) {
  auto size = polygon.size();
  if (Rotate(polygon[0], polygon[1], point) < 0 ||
      Rotate(polygon[0], polygon[size - 1], point) > 0) {
    return false;
  }
  size_t left = 1;
  size_t right = size - 1;
  while (right - left > 1) {
    auto middle = (left + right) / 2;
    if (Rotate(polygon[0], polygon[middle], point) < 0) {
      right = middle;
    } else {
      left = middle;
    }
  }
  return !IsIntersected(polygon[0], point, polygon[left], polygon[right]);
}

int main() {
  const size_t kCount = 3;
  std::vector<std::vector<Point>> polygons(3);
  for (size_t i = 0; i < kCount; ++i) {
    size_t number;
    std::cin >> number;
    polygons[i].resize(number);
    for (size_t j = 0; j < number; ++j) {
      std::cin >> polygons[i][j].x >> polygons[i][j].y;
    }
  }

  auto sum = Sum(polygons[0], polygons[1]);
  sum = Sum(sum, polygons[2]);
  sum = Clear(sum);

  size_t query_count;
  std::cin >> query_count;
  for (size_t i = 0; i < query_count; ++i) {
    Point point{};
    std::cin >> point.x >> point.y;
    point *= static_cast<long double>(kCount);
    if (IsLocated(sum, point)) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }
}