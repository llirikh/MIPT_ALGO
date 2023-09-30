#include <iostream>
#include <vector>
#include <queue>

struct Edge {
  long long to, cost, cap, flow, reverse_edge;
};

struct Solver {
  const long long kInf = 2e9 + 9;

  long long vertex_number;
  long long edge_number;

  std::vector<std::vector<Edge>> graph;
  std::vector<long long> state;
  std::vector<long long> from;
  std::vector<long long> from_edge;
  std::vector<long long> distance;
  std::deque<long long> queue;

  long long source;
  long long stock;
  long long max_flow;

  long long flow;
  long long cost;

  void Init();
  void Reset();

  void Read();
  void Spfa();
  void PushFlow();
  void Print();

  void Solve();
};

void Solver::Init() {
  source = 0;
  stock = vertex_number - 1;
  max_flow = 1e9;

  flow = 0;
  cost = 0;

  graph.resize(vertex_number + 1);
  state.resize(vertex_number + 1);
  from.resize(vertex_number + 1);
  from_edge.resize(vertex_number + 1);
  distance.resize(vertex_number + 1);
  queue.resize(vertex_number + 1);
}

void Solver::Reset() {
  fill(state.begin(), state.end(), 0);
  fill(distance.begin(), distance.end(), kInf);
  fill(from.begin(), from.end(), -1);
  state[source] = 1;
  distance[source] = 0;
  queue.clear();
  queue.push_back(source);
}

void Solver::Read() {
  std::cin >> vertex_number >> edge_number;
  Init();
  
  for (long long i = 0; i < edge_number; ++i) {
    long long from_vertex, to_vertex, cap_edge, flow_edge;
    std::cin >> from_vertex >> to_vertex >> cap_edge >> flow_edge;
    --from_vertex;
    --to_vertex;
    Edge straight_edge = {to_vertex, flow_edge, cap_edge, 0, static_cast<long long>(graph[to_vertex].size())};
    Edge reverse_edge = {from_vertex, -flow_edge, 0, 0, static_cast<long long>(graph[from_vertex].size())};
    graph[from_vertex].push_back(straight_edge);
    graph[to_vertex].push_back(reverse_edge);
  }
}

void Solver::Spfa() {
  while (!queue.empty()) {
    long long current_vertex = queue.front();
    queue.pop_front();
    state[current_vertex] = 0;

    for (long long i = 0; i < graph[current_vertex].size(); i++) {
      Edge &edge = graph[current_vertex][i];
      if (edge.flow >= edge.cap || distance[edge.to] <= distance[current_vertex] + edge.cost)
        continue;

      long long to = edge.to;
      distance[to] = distance[current_vertex] + edge.cost;
      from[to] = current_vertex;
      from_edge[to] = i;

      if (!state[to]) {
        queue.push_back(to);
        state[to] = 1;
      }
    }
  }
}

void Solver::PushFlow() {
  long long current_vertex = stock, add_flow = max_flow - flow;
  while (current_vertex != source) {
    add_flow = std::min(add_flow,
                        graph[from[current_vertex]][from_edge[current_vertex]].cap -
                            graph[from[current_vertex]][from_edge[current_vertex]].flow);
    current_vertex = from[current_vertex];
  }

  current_vertex = stock;
  while (current_vertex != source) {
    graph[from[current_vertex]][from_edge[current_vertex]].flow += add_flow;
    graph[current_vertex][graph[from[current_vertex]][from_edge[current_vertex]].reverse_edge].flow -= add_flow;
    cost += graph[from[current_vertex]][from_edge[current_vertex]].cost * add_flow;
    current_vertex = from[current_vertex];
  }

  flow += add_flow;
}

void Solver::Print() {
  std::cout << cost;
}

void Solver::Solve() {
  Read();
  while (flow < max_flow) {
    Reset();
    Spfa();
    if (distance[stock] == kInf) break;
    PushFlow();
  }
  Print();
}

int main() {
  Solver solver;
  solver.Solve();
}