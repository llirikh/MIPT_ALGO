#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Solver {
  int number_vertex, number_edges;

  int timer = 0;
  std::set<std::pair<int, int>> bridges;
  std::vector<std::vector<int>> graph;
  std::vector<int> time_in;
  std::vector<bool> used;
  std::vector<int> return_vertex;
  std::vector<std::pair<int, int>> edge;
  std::map<std::pair<int, int>, int> check;

  void Initialize();
  void Read();

  void Dfs(int vertex, int previous_vertex);

  void Solve();
  void PrintAnswer();
};

void Solver::Initialize() {
  graph.resize(number_vertex);
  time_in.assign(number_vertex, -1);
  used.assign(number_vertex, false);
  return_vertex.resize(number_vertex);
}

void Solver::Read() {
  std::cin >> number_vertex >> number_edges;

  Initialize();

  for (int i = 0; i < number_edges; ++i) {
    int from, to;
    std::cin >> from >> to;
    graph[from - 1].push_back(to - 1);
    graph[to - 1].push_back(from - 1);
    edge.emplace_back(from - 1, to - 1);
    std::pair<int, int> pair(from - 1, to - 1);
    std::pair<int, int> pair_r(to - 1, from - 1);
    if (check.find(pair) == check.end() &&
        check.find(pair_r) == check.end()) {
      check.insert({pair, 1});
      check.insert({pair_r, 1});
    } else {
      check[pair] += 1;
      check[pair_r] += 1;
    }
  }
}

void Solver::Dfs(int vertex, int previous_vertex) {
  time_in[vertex] = timer++;
  return_vertex[vertex] = time_in[vertex];
  used[vertex] = true;
  for (int to : graph[vertex]) {
    if (to == previous_vertex) {
      continue;
    }
    if (used[to]) {
      return_vertex[vertex] = std::min(return_vertex[vertex], time_in[to]);
    } else {
      Dfs(to, vertex);
      if (return_vertex[to] >= time_in[to]) {
        bridges.insert(std::pair<int, int>(vertex, to));
        bridges.insert(std::pair<int, int>(to, vertex));
      }
      return_vertex[vertex] = std::min(return_vertex[vertex], return_vertex[to]);
    }
  }
}

void Solver::Solve() {
  Read();

  for (int vertex = 0; vertex < number_vertex; ++vertex) {
    if (!used[vertex]) {
      Dfs(vertex, -1);
    }
  }

  for (auto i = bridges.begin(); i != bridges.end(); ++i) {
    if (check[*i] != 1) {
      bridges.erase(i);
    }
  }

  PrintAnswer();
}

void Solver::PrintAnswer() {
  std::cout << bridges.size() / 2 << '\n';
  for (int i = 0; i < number_edges; ++i) {
    if (bridges.find(edge[i]) != bridges.end()
        && check[edge[i]] == 1) {
      std::cout << i + 1 << ' ';
    }
  }
}

int main() {
  Solver solver;
  solver.Solve();

  return 0;
}