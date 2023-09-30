#include <bits/stdc++.h>

const long long kN = 2 * 1e5;
const long long kInf = 1e18;

std::vector<long long> infection_dist(kN, kInf);
long long nq;
long long mq;
long long kq;
std::set<long long> infection;
std::vector<std::vector<std::pair<long long, long long>>> graph(kN);
long long start;
long long finish;

void InitInfection() {
  std::priority_queue<std::pair<long long, long long>> queue;
  for (auto st : infection) {
    infection_dist[st] = 0;
    queue.emplace(0, st);
  }
  while (!queue.empty()) {
    long long len = -queue.top().first;
    long long vertex = queue.top().second;
    queue.pop();
    if (len > infection_dist[vertex]) {
      continue;
    }
    for (auto link : graph[vertex]) {
      long long to = link.first;
      long long length = link.second;
      if (infection_dist[to] > infection_dist[vertex] + length && length >= 0) {
        infection_dist[to] = infection_dist[vertex] + length;
        queue.emplace(-infection_dist[to], to);
      }
    }
  }
}

int main() {
  std::cin >> nq >> mq >> kq;
  for (long long i = 0; i < kq; ++i) {
    long long vertex;
    std::cin >> vertex;
    infection.insert(vertex - 1);
  }
  for (long long i = 0; i < mq; ++i) {
    long long from;
    long long to;
    long long weight;
    std::cin >> from >> to >> weight;
    graph[from - 1].emplace_back(to - 1, weight);
    graph[to - 1].emplace_back(from - 1, weight);
  }
  std::cin >> start >> finish;
  --start;
  --finish;

  InitInfection();

  std::vector<long long> dist(nq, kInf);
  dist[start] = 0;
  std::priority_queue<std::pair<long long, long long>> queue;
  queue.emplace(0, start);

  while (!queue.empty()) {
    long long len = -queue.top().first;
    long long vertex = queue.top().second;
    queue.pop();
    if (len > dist[vertex]) {
      continue;
    }
    for (auto link : graph[vertex]) {
      long long to = link.first;
      long long length = link.second;
      if (dist[to] > dist[vertex] + length && length >= 0) {
        dist[to] = dist[vertex] + length;
        if (dist[to] >= infection_dist[to]) {
          dist[to] = kInf;
          continue;
        }
        queue.emplace(-dist[to], to);
      }
    }
  }

  if (dist[finish] <= infection_dist[finish] && dist[finish] != kInf) {
    std::cout << dist[finish];
  } else {
    std::cout << -1;
  }
}