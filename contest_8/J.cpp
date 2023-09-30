#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 1e6 + 5;

struct Teleport {
  int cost_in, cost_out;
  vector<int> floors;
};

vector<Teleport> teleports;
int N, U, D, I, J, L;
int dist[MAXN], cost[MAXN];
bool used[MAXN];

void dijkstra(int start) {
  fill(dist, dist + N + 1, INF);
  fill(used, used + N + 1, false);
  fill(cost, cost + N + 1, INF);
  dist[start] = 0;
  cost[start] = 0;

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
  q.push({ 0, start });

  while (!q.empty()) {
    int v = q.top().second;
    q.pop();
    if (used[v]) continue;
    used[v] = true;

    for (int i = 0; i < L; i++) {
      auto& teleport = teleports[i];
      auto it = lower_bound(teleport.floors.begin(), teleport.floors.end(), v);
      if (it == teleport.floors.end()) continue;
      int u = *it;

      int cost_teleport_in = teleport.cost_in + I;
      int cost_teleport_out = teleport.cost_out + J;
      if (dist[v] + cost_teleport_in < dist[u]) {
        dist[u] = dist[v] + cost_teleport_in;
        cost[u] = cost[v] + 1;
        q.push({ dist[u], u });
      } else if (dist[v] + cost_teleport_in == dist[u]) {
        cost[u] = min(cost[u], cost[v] + 1);
      }
    }

    if (v > 1 && !used[v - 1]) {
      int u = v - 1;
      int cost_step = U;
      if (dist[v] + cost_step < dist[u]) {
        dist[u] = dist[v] + cost_step;
        cost[u] = cost[v] + 1;
        q.push({ dist[u], u });
      } else if (dist[v] + cost_step == dist[u]) {
        cost[u] = min(cost[u], cost[v] + 1);
      }
    }

    if (v < N && !used[v + 1]) {
      int u = v + 1;
      int cost_step = D;
      if (dist[v] + cost_step < dist[u]) {
        dist[u] = dist[v] + cost_step;
        cost[u] = cost[v] + 1;
        q.push({ dist[u], u });
      } else if (dist[v] + cost_step == dist[u]) {
        cost[u] = min(cost[u], cost[v] + 1);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> N >> U >> D >> I >> J >> L;

  teleports.resize(L);
  for (int i = 0; i < L; i++) {
    int k;
    cin >> k;
    teleports[i].floors.resize(k);
    for (int j = 0; j < k; j++) {
      cin >> teleports[i].floors[j];
    }
    cin >> teleports[i].cost_in >> teleports[i].cost_out;
  }
}