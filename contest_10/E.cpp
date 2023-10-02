// no_concepts
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

static const char kZeroSymbol = '0';
static const int kSigma = 10;

struct Vertex {
  bool is_terminal;
  int depth;
  int terminal_vertex_count;
  int next[kSigma]{};

  Vertex(bool is_terminal, int depth);
};

Vertex::Vertex(bool is_terminal, int depth)
    : is_terminal{is_terminal}, depth{depth} {
  terminal_vertex_count = 0;
  memset(next, -1, sizeof(next));
}

struct Trie {
  static const int kAnswerSize = 1e6 + 1;
  std::vector<Vertex> data;
  int answer[kAnswerSize]{};

  Trie();
  Vertex* GetRoot();
  void AddWord(const std::string& word);
  void InitAnswerArray(int k);
  int GetAnswer(int length) { return answer[length]; }
};

Trie::Trie() {
  data.emplace_back(false, 0);
  std::memset(answer, 0, sizeof(answer));
}

Vertex* Trie::GetRoot() { return data.data(); }

void Trie::AddWord(const std::string& word) {
  Vertex* current_vertex = GetRoot();
  ++current_vertex->terminal_vertex_count;
  for (int i = 0; i < static_cast<int>(word.size()); ++i) {
    if (current_vertex->next[word[i] - kZeroSymbol] == -1) {
      current_vertex->next[word[i] - kZeroSymbol] =
          static_cast<int>(data.size());
      data.emplace_back(i == static_cast<int>(word.size()) - 1,
                        current_vertex->depth + 1);
      current_vertex = &data[data.size() - 1];
      ++current_vertex->terminal_vertex_count;
      continue;
    }
    current_vertex = &data[current_vertex->next[word[i] - kZeroSymbol]];
    ++current_vertex->terminal_vertex_count;
    if (i == static_cast<int>(word.size()) - 1) {
      current_vertex->is_terminal = true;
    }
  }
}

void Trie::InitAnswerArray(int k) {
  std::queue<int> queue;
  queue.push(0);
  while (!queue.empty()) {
    int current_vertex_idx = queue.front();
    queue.pop();
    answer[data[current_vertex_idx].depth] +=
        static_cast<int>(data[current_vertex_idx].terminal_vertex_count >= k);
    for (int to : data[current_vertex_idx].next) {
      if (to != -1) {
        queue.push(to);
      }
    }
  }
}

int main() {
  SpeedUp();
  int words_number;
  int fake_size;
  std::cin >> words_number >> fake_size;

  Trie trie;
  for (int i = 0; i < words_number; ++i) {
    std::string word;
    std::cin >> word;
    std::string modified_word;
    for (size_t j = 0; j < word.size(); ++j) {
      modified_word += word[j];
      modified_word += word[word.size() - 1 - j];
    }
    trie.AddWord(modified_word);
  }
  trie.InitAnswerArray(fake_size);

  int query_number;
  std::cin >> query_number;
  for (int i = 0; i < query_number; ++i) {
    int length;
    std::cin >> length;
    std::cout << trie.GetAnswer(2 * length) << '\n';
  }
}