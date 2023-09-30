#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

//TODO Разбить по функциям

const long long INF = 9223372036854775807;

int main() {
  long long nV, nE;
  std::cin >> nV >> nE;

  std::vector<std::vector<long long>> mem(nE);

  long long s = 0;
  long long t = nV - 1;
  std::vector<std::vector<long long>> cap(nV, std::vector<long long>(nV, 0));
  for (long long i = 0; i < nE; ++i) {
    long long from, to, c;
    std::cin >> from >> to >> c;
    --from;
    --to;
    mem[i].push_back(from);
    mem[i].push_back(to);
    mem[i].push_back(c);
    cap[from][to] += c;
  }

  std::vector<std::vector<long long>> flow(nV, std::vector<long long>(nV, 0));
  std::vector<long long> excess(nV, 0);
  std::vector<long long> height(nV, 0);
  std::vector<long long> seen(nV, 0);
  height[s] = nV;
  excess[s] = INF;

  std::queue<long long> q;
  for (long long v = 0; v < nV; ++v) {
    if (v != s) {
      long long d = std::min(excess[s], cap[s][v] - flow[s][v]);
      flow[s][v] += d;
      flow[v][s] -= d;
      excess[v] += d;
      excess[s] -= d;
      if (d && excess[v] == d) {
        q.push(v);
      }
    }
  }

  while (!q.empty()) {
    long long cur = q.front();
    q.pop();
    assert(excess[cur] > 0);
    if (cur != s && cur != t) {
      while (excess[cur] > 0) {
        if (seen[cur] < nV) {
          long long v = seen[cur];
          if (cap[cur][v] - flow[cur][v] > 0 && height[cur] > height[v]) {
            long long d = std::min(excess[cur], cap[cur][v] - flow[cur][v]);
            flow[cur][v] += d;
            flow[v][cur] -= d;
            excess[cur] -= d;
            excess[v] += d;
            if (d && excess[v] == d) {
              q.push(v);
            }
          } else {
            ++seen[cur];
          }
        } else {
          long long d = INF;
          for (long long i = 0; i < nV; ++i) {
            if (cap[cur][i] - flow[cur][i] > 0) {
              d = std::min(d, height[i]);
            }
          }
          if (d < INF) {
            height[cur] = d + 1;
          }
          seen[cur] = 0;
        }
      }
    }
  }
  std::cout << excess[t] << '\n';
  for (auto& list : mem) {
    if (flow[list[0]][list[1]] > list[2]) {
      std::cout << list[2] << '\n';
      flow[list[0]][list[1]] -= list[2];
    } else {
      std::cout << flow[list[0]][list[1]] << '\n';
      flow[list[0]][list[1]] = 0;
    }
  }
}