#include <iostream>
#include <vector>

void Dfs(int vertex, std::vector<bool>& used, std::vector<std::vector<int>>& graph) {
  used[vertex] = true;
  for (int to : graph[vertex]) {
    if (!used[to]) {
      Dfs(to, used, graph);
    }
  }
}

void Read(int& vertical_coordinate, int& horizontal_coordinate, std::vector<std::vector<int>>& graph) {
  std::cin >> vertical_coordinate >> horizontal_coordinate;
  for (int i = 0; i < vertical_coordinate; ++i) {
    int current_value;
    std::cin >> current_value;
    for (int j = 0; j < current_value; ++j) {
      int to;
      std::cin >> to;
      graph[i].push_back(to + vertical_coordinate - 1);
    }
  }
}

void Print(std::vector<int>& answer_1, std::vector<int>& answer_2) {
  std::cout << answer_1.size() + answer_2.size() << '\n';
  std::cout << answer_1.size() << ' ';
  for (int vertex : answer_1) {
    std::cout << vertex + 1<< ' ';
  }
  std::cout << '\n' << answer_2.size() << ' ';
  for (int vertex : answer_2) {
    std::cout << vertex + 1 << ' ';
  }
}

int main() {
  const int kInf = 8000;
  std::vector<bool> used(kInf, false);
  std::vector<std::vector<int>> graph(kInf, std::vector<int>());
  int vertical_coordinate, horizontal_coordinate;

  Read(vertical_coordinate, horizontal_coordinate, graph);

  std::vector<int> free;
  for (int i = 0; i < vertical_coordinate; ++i) {
    int to;
    std::cin >> to;
    if (to != 0) {
      graph[to + vertical_coordinate - 1].push_back(i);
    } else {
      free.push_back(i);
    }
  }

  for (int vertex : free) {
    Dfs(vertex, used, graph);
  }

  std::vector<int> answer_1, answer_2;
  for (int i = 0; i < vertical_coordinate; ++i) {
    if (!used[i]) {
      answer_1.push_back(i);
    }
  }
  for (int i = 0; i < horizontal_coordinate; ++i) {
    if (used[i + vertical_coordinate]) {
      answer_2.push_back(i);
    }
  }

  Print(answer_1, answer_2);
}