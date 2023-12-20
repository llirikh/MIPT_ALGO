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

void Reorder(std::vector<Point>& polygon) {
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

long double Scalar(const Point& lhs, const Point& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

long double CosAngle(const Point& lhs, const Point& rhs) {
  return Scalar(lhs, rhs) / (lhs.Length() * rhs.Length());
}

std::vector<Point> Sum(std::vector<Point>& polygon1,
                       std::vector<Point>& polygon2) {
  Reorder(polygon1);
  Reorder(polygon2);

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

  return sum;
}

long double Distance(Point& point1, Point& point2, Point& point3) {
  long double aa = point2.y - point1.y;
  long double bb = point1.x - point2.x;
  long double cc = -(aa * point1.x + point1.y * (point1.x - point2.x));
  long double d3 = std::abs(aa * point3.x + bb * point3.y + cc) /
                   std::sqrt(aa * aa + bb * bb);
  if ((point3.x - point1.x) * (point2.x - point1.x) +
              (point3.y - point1.y) * (point2.y - point1.y) <
          0 ||
      (point3.x - point2.x) * (point1.x - point2.x) +
              (point3.y - point2.y) * (point1.y - point2.y) <
          0) {
    auto dd1 = std::sqrt((point1.x - point3.x) * (point1.x - point3.x) +
                         (point1.y - point3.y) * (point1.y - point3.y));
    auto dd2 = std::sqrt((point2.x - point3.x) * (point2.x - point3.x) +
                         (point2.y - point3.y) * (point2.y - point3.y));
    d3 = std::min(dd1, dd2);
  }
  return d3;
}

int main() {
  size_t number1;
  size_t number2;
  std::cin >> number1 >> number2;

  std::vector<Point> polygon1(number1);
  for (size_t i = 0; i < number1; ++i) {
    std::cin >> polygon1[i].x >> polygon1[i].y;
  }

  std::vector<Point> polygon2(number2);
  for (size_t i = 0; i < number2; ++i) {
    std::cin >> polygon2[i].x >> polygon2[i].y;
    polygon2[i] *= -1;
  }

  auto sum = Sum(polygon1, polygon2);
  Point point{0, 0};
  long double dist = Distance(sum[0], sum[sum.size() - 1], point);
  for (size_t i = 0; i < sum.size() - 1; ++i) {
    dist = std::min(dist, Distance(sum[i], sum[i + 1], point));
  }

  const int kPrecision = 6;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  const long double kSeconds = 60;
  std::cout << std::max(static_cast<long double>(0), dist - kSeconds);
}