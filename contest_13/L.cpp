#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;
};

int CrossProduct(const Point& oo, const Point& aa, const Point& bb) {
  return (aa.x - oo.x) * (bb.y - oo.y) - (aa.y - oo.y) * (bb.x - oo.x);
}

std::vector<Point> ConvexHull(std::vector<Point>& points) {
  int nn = static_cast<int>(points.size());
  if (nn <= 1)
    return points;

  sort(points.begin(), points.end(), [](const Point& aa, const Point& bb) {
    return aa.x < bb.x || (aa.x == bb.x && aa.y < bb.y);
  });

  std::vector<Point> lowerHull;
  for (int i = 0; i < nn; ++i) {
    while (lowerHull.size() >= 2 &&
           CrossProduct(lowerHull[lowerHull.size() - 2],
                        lowerHull[lowerHull.size() - 1], points[i]) <= 0) {
      lowerHull.pop_back();
    }
    lowerHull.push_back(points[i]);
  }

  std::vector<Point> upperHull;
  for (int i = nn - 1; i >= 0; --i) {
    while (upperHull.size() >= 2 &&
           CrossProduct(upperHull[upperHull.size() - 2],
                        upperHull[upperHull.size() - 1], points[i]) <= 0) {
      upperHull.pop_back();
    }
    upperHull.push_back(points[i]);
  }

  lowerHull.pop_back();
  upperHull.pop_back();
  lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end());
  return lowerHull;
}

int QueryMaxValue(const std::vector<Point>& hull, int aa, int bb) {
  int maxVal = -1e9;
  for (const Point& pt : hull) {
    maxVal = std::max(maxVal, aa * pt.x + bb * pt.y);
  }
  return maxVal;
}

int main() {
  int nn;
  std::cin >> nn;

  std::vector<Point> points(nn);
  for (int i = 0; i < nn; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }

  std::vector<Point> convexH = ConvexHull(points);

  int mm;
  std::cin >> mm;
  while (mm--) {
    std::string type;
    std::cin >> type;
    if (type == "get") {
      int aa;
      int bb;
      std::cin >> aa >> bb;
      int result = QueryMaxValue(convexH, aa, bb);
      std::cout << result << "\n";
    } else if (type == "add") {
      int xx, yy;
      std::cin >> xx >> yy;
      points.push_back({xx, yy});
      ++nn;
      convexH = ConvexHull(points);
    }
  }

  return 0;
}