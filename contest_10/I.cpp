// no_concepts
#include <iostream>
#include <queue>
#include <vector>

static const char kZeroSymbol = '0';
static const int kSigma = 2;

struct Vertex {
  int prev;
  int idx;
  bool is_terminal;
  int link = -1;
  int compressed_link = -1;
  std::vector<int> next = std::vector<int>(kSigma, -1);
  std::vector<int> go = std::vector<int>(kSigma, -1);
};

struct Trie {
  std::vector<Vertex> data = std::vector<Vertex>(1, Vertex{-1, 0, false});
  std::vector<int> used;

  Vertex* GetRoot();
  void AddWord(const std::string& word);
  void InitGo(Vertex* vertex);
  void InitLinks();
  bool HasCycle(int vertex_idx);
};

Vertex* Trie::GetRoot() { return data.data(); }

void Trie::AddWord(const std::string& word) {
  Vertex* current_vertex = GetRoot();
  for (int i = 0; i < static_cast<int>(word.size()); ++i) {
    if (current_vertex->next[word[i] - kZeroSymbol] == -1) {
      current_vertex->next[word[i] - kZeroSymbol] =
          static_cast<int>(data.size());
      data.push_back(Vertex{current_vertex->idx, static_cast<int>(data.size()),
                            i == static_cast<int>(word.size()) - 1});
      current_vertex = &data[data.size() - 1];
      continue;
    }
    current_vertex = &data[current_vertex->next[word[i] - kZeroSymbol]];
    if (i == static_cast<int>(word.size()) - 1) {
      current_vertex->is_terminal = true;
    }
  }
}

void Trie::InitGo(Vertex* vertex) {
  for (int i = 0; i < kSigma; ++i) {
    if (vertex->next[i] != -1) {
      vertex->go[i] = vertex->next[i];
      continue;
    }
    vertex->go[i] = data[vertex->link].go[i];
  }
}

void Trie::InitLinks() {
  std::queue<int> queue;
  used = std::vector<int>(data.size(), 0);
  Vertex* root = GetRoot();
  root->go = root->next;
  for (int next_vertex_idx : root->next) {
    if (next_vertex_idx != -1) {
      queue.push(next_vertex_idx);
      data[next_vertex_idx].link = 0;
    }
  }
  Vertex* current_vertex;
  Vertex* parent_vertex;
  Vertex* temp_vertex;
  int link_letter = -1;
  while (!queue.empty()) {
    current_vertex = &data[queue.front()];
    parent_vertex = &data[current_vertex->prev];
    queue.pop();
    for (int next_vertex_idx : current_vertex->next) {
      if (next_vertex_idx != -1) {
        queue.push(next_vertex_idx);
      }
    }
    if (current_vertex->link != -1) {
      InitGo(current_vertex);
      continue;
    }
    for (size_t i = 0; i < parent_vertex->next.size(); ++i) {
      if (parent_vertex->next[i] == current_vertex->idx) {
        link_letter = static_cast<int>(i);
        break;
      }
    }
    temp_vertex = &data[parent_vertex->link];
    while (temp_vertex->prev != -1 && temp_vertex->next[link_letter] == -1) {
      temp_vertex = &data[temp_vertex->link];
    }
    if (temp_vertex->next[link_letter] != -1) {
      current_vertex->link = temp_vertex->next[link_letter];
    } else {
      current_vertex->link = 0;
    }
    if (data[current_vertex->link].is_terminal) {
      current_vertex->compressed_link = current_vertex->link;
    } else {
      current_vertex->compressed_link =
          data[current_vertex->link].compressed_link;
    }
    InitGo(current_vertex);
  }
}

bool Trie::HasCycle(int vertex_idx = 0) {
  bool answer = false;
  used[vertex_idx] = 1;
  for (int to : data[vertex_idx].go) {
    if (to == -1 || used[to] == 2 || data[to].is_terminal ||
        data[to].compressed_link != -1) {
      continue;
    }
    if (used[to] == 1) {
      return true;
    }
    answer = answer || HasCycle(to);
  }
  used[vertex_idx] = 2;
  return answer;
}

int main() {
  int number = 0;
  std::cin >> number;

  Trie trie;
  for (int i = 0; i < number; ++i) {
    std::string str;
    std::cin >> str;
    trie.AddWord(str);
  }
  trie.InitLinks();

  if (trie.HasCycle()) {
    std::cout << "TAK";
  } else {
    std::cout << "NIE";
  }
}