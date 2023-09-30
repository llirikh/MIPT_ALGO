#include <iostream>
#include <vector>
#include <queue>
#include <climits>

int main() {
  const long long kInfinity = INT_MAX;
  long long query_number;
  std::cin >> query_number;
  for (long long i = 0; i < query_number; ++i) {
    long long vertex_number;
    long long edge_number;
    long long start;
    std::cin >> vertex_number >> edge_number;
    std::vector<std::vector<std::pair<long long, long long>>> graph(vertex_number);
    for (long long j = 0; j < edge_number; ++j) {
      long long from;
      long long to;
      long long weight;
      std::cin >> from >> to >> weight;
      graph[from].emplace_back(to, weight);
      graph[to].emplace_back(from, weight);
    }
    std::cin >> start;

    std::vector<long long> distantion(vertex_number, kInfinity);
    distantion[start] = 0;
    std::priority_queue<std::pair<long long, long long>> queue;
    queue.emplace(0, start);

    while (!queue.empty()) {
      long long len = -queue.top().first;
      long long vertex = queue.top().second;
      queue.pop();
      if (len > distantion[vertex]) {
        continue;
      }
      for (auto link : graph[vertex]) {
        long long to = link.first;
        long long length = link.second;
        if (distantion[to] > distantion[vertex] + length && length >= 0) {
          distantion[to] = distantion[vertex] + length;
          queue.emplace(-distantion[to], to);
        }
      }
    }
    for (auto& item : distantion) {
      std::cout << item << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}