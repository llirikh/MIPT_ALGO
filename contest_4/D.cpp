#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

void Theory1(int n, std::vector<std::pair<long long, long long>>& array) {
  long long ans = 0;
  for (int i = 0; i < n; ++i) {
    std::unordered_map<long long, long long> dist;
    long long x1 = array[i].first;
    long long y1 = array[i].second;
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        long long x2 = array[j].first;
        long long y2 = array[j].second;
        long long d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        ++dist[d];
      }
    }
    for (std::pair<long long, long long> elem : dist) {
      ans += elem.second * (elem.second - 1) / 2;
    }
  }
  std::cout << ans;
}

void Theory2(long long n, std::vector<std::pair<long long, long long>>& array) {
  long long ans = 0;
  std::sort(array.begin(), array.end());

  std::pair<long long, long long> cur_point = array[0];
  long long cur_cnt = 0;
  bool flag = true;
  for (int i = 0; i < n; ++i) {
    if (array[i] == cur_point) {
      cur_cnt++;
      flag = true;
    } else {
      cur_point = array[i];
      if (cur_cnt > 2) {
        ans += (cur_cnt * (cur_cnt - 1) * (cur_cnt - 2) / 6);
      }
      cur_cnt = 1;
      flag = false;
    }
  }
  if (flag && (cur_cnt > 2)) {
    ans += (cur_cnt * (cur_cnt - 1) * (cur_cnt - 2) / 6);
  }
  std::cout << ans;
}

int main() {
  int n, t;
  std::cin >> n >> t;
  std::vector<std::pair<long long, long long>> array;
  for (int i = 0; i < n; ++i) {
    long long x, y;
    std::cin >> x >> y;
    array.push_back({x, y});
  }
  if (t == 1) {
    Theory1(n, array);
  } else {
    Theory2(n, array);
  }
}