#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  long double x;
  long double y;
};

long double Rotate(Point& aa, Point& bb, Point& cc) {
  return (bb.x - aa.x) * (cc.y - bb.y) - (bb.y - aa.y) * (cc.x - bb.x);
}

bool Comparator(Point& point1, Point& point2, Point& extreme_point) {
  auto rotate = Rotate(extreme_point, point1, point2);
  if (rotate == 0) {
    if (point1.x != point2.x) {
      return point1.x < point2.x;
    }
    return point1.y < point2.y;
  }
  return rotate < 0;
}

size_t GetExtremePointIndex(std::vector<Point>& points) {
  size_t index = 0;
  for (size_t i = 1; i < points.size(); ++i) {
    if (points[i].x < points[index].x ||
        (points[i].x == points[index].x && points[i].y < points[index].y)) {
      index = i;
    }
  }
  return index;
}

std::vector<Point> GetConvexHull(std::vector<Point>& points) {
  std::swap(points[0], points[GetExtremePointIndex(points)]);
  auto extreme_point = points[0];

  std::sort(points.begin() + 1, points.end(),
            [&extreme_point](Point& lhs, Point& rhs) {
              return Comparator(lhs, rhs, extreme_point);
            });

  std::vector<Point> stack{points[0], points[1]};
  for (size_t i = 2; i < points.size(); ++i) {
    while (stack.size() >= 2 &&
           Rotate(stack[stack.size() - 2], stack[stack.size() - 1],
                  points[i]) >= 0) {
      stack.pop_back();
    }
    stack.push_back(points[i]);
  }

  return stack;
}

long double GetSquare(std::vector<Point>& points) {
  long double square = 0;

  auto point1 = points[0];
  for (size_t i = 1; i < points.size() - 1; ++i) {
    auto point2 = points[i];
    auto point3 = points[i + 1];
    square += std::abs((point2.x - point1.x) * (point3.y - point1.y) -
                       (point3.x - point1.x) * (point2.y - point1.y)) /
              2;
  }
-
  return square;
}

int main() {
  int number;
  std::cin >> number;

  std::vector<Point> points(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }
  auto convex_hull = GetConvexHull(points);

  std::cout << std::fixed << std::setprecision(0);
  std::cout << convex_hull.size() << '\n';
  for (auto& point : convex_hull) {
    std::cout << point.x << ' ' << point.y << '\n';
  }
  std::cout << std::fixed << std::setprecision(1);
  std::cout << GetSquare(convex_hull);
}