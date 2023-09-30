#include <vector>
#include <climits>
#include <iostream>

//TODO Разбить по функциям

void count_vals(int n, std::vector<long long>& used, std::vector<std::vector<long long>>& graph,
                long long& used_x_idx, long long& used_y_idx, std::vector<long long>& u, std::vector<long long>& v,
                std::vector<long long>& mins, std::vector<long long>& prev, long long& j) {
  for (long long j1 = 0; j1 < n; j1++) {
    if (!used[j1]) {
      if (graph[used_x_idx][j1] - u[used_x_idx] - v[j1] < mins[j1]) {
        mins[j1] = graph[used_x_idx][j1] - u[used_x_idx] - v[j1];
        prev[j1] = used_y_idx;
      }
      if (j==-1 || mins[j1] < mins[j])
        j = j1;
    }
  }
}

void count_dist(long long& n, std::vector<long long>& mins, long long& j, long long& i, std::vector<long long>& used,
                std::vector<long long>& u, std::vector<long long>& v, std::vector<long long>& used_idx) {
  long long dist = mins[j];
  for (long long j1 = 0; j1 < n; j1++) {
    if (used[j1]) {
      u[used_idx[j1]] += dist;
      v[j1] -= dist;
    } else {
      mins[j1] -= dist;
    }
  }
  u[i] += dist;
}

int main() {
  long long n;
  std::cin >> n;

  std::vector<std::vector<long long>> graph(n, std::vector<long long>(n));

  for (long long i = 0; i < n; ++i) {
    for (long long j = 0; j < n; ++j) {
      std::cin >> graph[i][j];
    }
  }

  const long long INF = INT_MAX;
  std::vector<long long> u(n, 0);
  std::vector<long long> v(n, 0);
  std::vector<long long> used_idx(n, -1);

  for (long long i = 0; i < n; i++) {
    std::vector<long long> prev(n, -1);
    std::vector<long long> mins(n, INF);
    std::vector<long long> used(n, 0);

    long long used_x_idx = i, used_y_idx = -1, j;
    while (used_x_idx != -1) {
      j = -1;
      count_vals(n, used, graph, used_x_idx, used_y_idx, u, v, mins, prev, j);
      count_dist(n, mins, j, i, used, u, v, used_idx);
      used[j] = 1;
      used_y_idx = j;
      used_x_idx = used_idx[j];
    }

    for (; prev[j] != -1; j = prev[j]) {
      used_idx[j] = used_idx[prev[j]];
    }
    used_idx[j] = i;
  }

  std::vector<std::pair<long long, long long>> result;
  for (long long j = 0; j < n; j++) {
    if (used_idx[j] != -1)
      result.emplace_back(used_idx[j], j);
  }

  long long sum = 0;
  for (auto item : result) {
    sum += graph[item.first][item.second];
  }

  std::cout << sum << '\n';
  for (auto item : result) {
    std::cout << item.first + 1 << ' ' << item.second + 1 << '\n';
  }
}