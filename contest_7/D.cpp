#include <algorithm>
#include <iostream>
#include <vector>

struct Solver {
  int number_vertex, number_edges;

  int timer = 0;
  std::vector<std::vector<int>> graph;
  std::vector<std::vector<int>> graph_reverse;
  std::vector<int> time_in;
  std::vector<std::vector<int>> time_out;
  std::vector<std::string> color;
  std::vector<int> new_vertex;
  std::vector<int> previous;
  std::vector<std::vector<int>> answer;

  void Initialize();
  void Read();

  void DfsReverse(int vertex);
  void Dfs(int vertex);

  void Solve();
  void PrintAnswer();
};

void Solver::Initialize() {
  graph.resize(number_vertex);
  graph_reverse.resize(number_vertex);
  time_in.assign(number_vertex, -1);
  time_out.assign(number_vertex, std::vector<int>(2));
  color.assign(number_vertex, "WHITE");
  new_vertex.resize(number_vertex);
  previous.resize(number_vertex);
}

void Solver::Read() {
  std::cin >> number_vertex >> number_edges;

  Initialize();

  for (int i = 0; i < number_edges; ++i) {
    int vertex_from, vertex_to;
    std::cin >> vertex_from >> vertex_to;
    graph[vertex_from - 1].push_back(vertex_to - 1);
    graph_reverse[vertex_to - 1].push_back(vertex_from - 1);
  }
}

void Solver::DfsReverse(int vertex) {
  answer[answer.size() - 1].push_back(vertex);
  color[vertex] = "GREY";
  for (int to : graph_reverse[vertex]) {
    if (color[to] != "WHITE") {
      continue;
    }
    DfsReverse(to);
  }
  color[vertex] = "BLACK";
}

void Solver::Dfs(int vertex) {
  time_in[vertex] = timer++;
  color[vertex] = "GREY";
  for (int to : graph[vertex]) {
    if (color[to] != "WHITE") {
      continue;
    }
    Dfs(to);
  }
  time_out[vertex][0] = timer++;
  color[vertex] = "BLACK";
}

void Solver::PrintAnswer() {
  for (long unsigned int i = 0; i < answer.size(); ++i) {
    for (int vertex : answer[i]) {
      previous[vertex] = i + 1;
    }
  }

  std::cout << answer.size() << '\n';
  for (int item : previous) {
    std::cout << item << ' ';
  }
}

void Solver::Solve() {
  Read();

  for (int vertex = 0; vertex < number_vertex; ++vertex) {
    time_out[vertex][1] = vertex;
    if (color[vertex] == "WHITE") {
      Dfs(vertex);
    }
  }
  std::sort(time_out.begin(), time_out.begin() + number_vertex);
  for (int i = number_vertex - 1; i >= 0; --i) {
    new_vertex[number_vertex - 1 - i] = time_out[i][1];
    color[i] = "WHITE";
  }

  for (int vertex : new_vertex) {
    if (color[vertex] == "WHITE") {
      answer.emplace_back();
      DfsReverse(vertex);
    }
  }

  PrintAnswer();
}

int main() {

  Solver solver;
  solver.Solve();

  return 0;
}