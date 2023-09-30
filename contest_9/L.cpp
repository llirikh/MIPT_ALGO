#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

const long long INF = 1e9;
long long nV, nE;

void dfs(long long s, std::vector<bool>& used, std::vector<std::vector<long long>>& cap, std::vector<std::vector<long long>>& flow) {
  used[s] = true;
  for (long long v = 0; v < nV; ++v) {
    if (cap[s][v] != 0 && !used[v] && flow[s][v] < cap[s][v]) {
      dfs(v, used, cap, flow);
    }
  }
}

int main() {
  std::cin >> nV >> nE;

  long long s = 0;
  long long t = nV - 1;
  std::vector<std::pair<long long, long long>> mem;
  std::vector<std::vector<long long>> cap(nV, std::vector<long long>(nV, 0));
  for (long long i = 0; i < nE; ++i) {
    long long from, to, c;
    std::cin >> from >> to >> c;
    --from;
    --to;
    mem.emplace_back(from, to);
    cap[from][to] = c;
    cap[to][from] = c;
  }

  std::vector<std::vector<long long>> flow(nV, std::vector<long long>(nV, 0));
  std::vector<long long> excess(nV, 0);
  std::vector<long long> height(nV, 0);
  std::vector<long long> seen(nV, 0);
  height[s] = nV;
  excess[s] = INF;

  std::queue<long long> q;
  for (long long v = 0; v < nV; ++v) {
    if (v != s && cap[s][v] > 0) {
      long long d = cap[s][v] - flow[s][v];
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

  std::vector<bool> used(nV, false);
  dfs(s, used, cap, flow);

  long long count = 0;
  long long sum = 0;
  for (long long i = 0; i < nE; ++i) {
    if (used[mem[i].first] && !used[mem[i].second]) {
      ++count;
      sum += cap[mem[i].first][mem[i].second];
    } else if (used[mem[i].second] && !used[mem[i].first]) {
      ++count;
      sum += cap[mem[i].second][mem[i].first];
    }
  }
  std::cout << count << ' ';
  std::cout << sum << '\n';
  for (long long i = 0; i < nE; ++i) {
    if (used[mem[i].first] && !used[mem[i].second] || used[mem[i].second] && !used[mem[i].first]) {
      std::cout << i + 1 << ' ';
    }
  }
}