#include <cstring>
#include <iostream>
#include <queue>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

static const int kSigma = 26;
static const char kZeroSymbol = 'a';

struct Vertex {
  int prev;
  int idx;
  bool is_terminal;
  int link_symbol;
  int link = -1;
  int compressed_link = -1;
  std::vector<int> word_idx;
  int word_size = -1;
  int next[kSigma]{};

  Vertex(int prev, int idx, bool is_terminal, int link_symbol);
};

Vertex::Vertex(int prev, int idx, bool is_terminal, int link_symbol)
    : prev(prev), idx(idx), is_terminal(is_terminal), link_symbol(link_symbol) {
  link = -1;
  compressed_link = -1;
  word_size = -1;
  std::memset(next, -1, sizeof(next));
}

struct Trie {
  std::vector<Vertex> data;
  std::vector<std::vector<int>> occurrence;
  int count = -1;

  Trie();
  Vertex* GetRoot();
  void AddWord(const std::string& word);
  void InitLinks();
  void BlaBla(Vertex*& current_vertex, int current_symbol);
  void Something(int current_terminal_vertex_id, size_t id) {
    while (current_terminal_vertex_id != -1) {
      if (data[current_terminal_vertex_id].is_terminal) {
        for (int idx : data[current_terminal_vertex_id].word_idx) {
          occurrence[idx].push_back(static_cast<int>(id) -
                                    data[current_terminal_vertex_id].word_size +
                                    1);
        }
      }
      current_terminal_vertex_id =
          data[current_terminal_vertex_id].compressed_link;
    }
  }
  void SearchOccurrences(const std::string& text);
  void EditMatrix(std::vector<std::vector<int>>& matrix, int idx);
  void EditReverseMatrix(std::vector<std::vector<int>>& matrix, int idx);
};

Trie::Trie() { data.emplace_back(-1, 0, false, -1); }

Vertex* Trie::GetRoot() { return data.data(); }

void Trie::AddWord(const std::string& word) {
  Vertex* current_vertex = GetRoot();
  count++;
  for (size_t i = 0; i < word.size(); ++i) {
    int current_symbol = word[i] - kZeroSymbol;
    if (current_vertex->next[current_symbol] == -1) {
      current_vertex->next[current_symbol] = static_cast<int>(data.size());
      data.emplace_back(current_vertex->idx, static_cast<int>(data.size()),
                        i == word.size() - 1, current_symbol);
      if (i == word.size() - 1) {
        data[data.size() - 1].word_idx.push_back(count);
        data[data.size() - 1].word_size = static_cast<int>(word.size());
      }
      current_vertex = &data[data.size() - 1];
      continue;
    }
    current_vertex = &data[current_vertex->next[word[i] - kZeroSymbol]];
    if (i == (word.size() - 1)) {
      current_vertex->is_terminal = true;
      current_vertex->word_idx.push_back(count);
      current_vertex->word_size = static_cast<int>(word.size());
    }
  }
}

void Trie::InitLinks() {
  std::queue<int> queue;
  // open root vertex
  Vertex* root = GetRoot();
  for (int next_vertex_idx : root->next) {
    if (next_vertex_idx != -1) {
      queue.push(next_vertex_idx);
      data[next_vertex_idx].link = 0;
    }
  }

  Vertex* current_vertex;
  Vertex* parent_vertex;
  Vertex* temp_vertex;
  while (!queue.empty()) {
    current_vertex = &data[queue.front()];
    parent_vertex = &data[current_vertex->prev];
    queue.pop();
    // open current_vertex
    for (int next_vertex_idx : current_vertex->next) {
      if (next_vertex_idx != -1) {
        queue.push(next_vertex_idx);
      }
    }
    // current_vertex is child of root
    if (current_vertex->link != -1) {
      continue;
    }
    // search for vertex to link
    temp_vertex = &data[parent_vertex->link];
    while (temp_vertex->prev != -1 &&
           temp_vertex->next[current_vertex->link_symbol] == -1) {
      temp_vertex = &data[temp_vertex->link];
    }
    if (temp_vertex->next[current_vertex->link_symbol] != -1) {
      current_vertex->link = temp_vertex->next[current_vertex->link_symbol];
    } else {
      current_vertex->link = 0;
    }
    // search compressed_link for current_vertex
    if (data[current_vertex->link].is_terminal) {
      current_vertex->compressed_link = current_vertex->link;
    } else {
      current_vertex->compressed_link =
          data[current_vertex->link].compressed_link;
    }
  }
}

void Trie::BlaBla(Vertex*& current_vertex, int current_symbol) {
  while (current_vertex->prev != -1 &&
         current_vertex->next[current_symbol] == -1) {
    current_vertex = &data[current_vertex->link];
  }
}

void Trie::SearchOccurrences(const std::string& text) {
  occurrence = std::vector<std::vector<int>>(count + 1);
  Vertex* current_vertex = GetRoot();
  for (size_t i = 0; i < text.size(); ++i) {
    bool go_to_next_vertex = true;
    int current_symbol = text[i] - kZeroSymbol;
    // current_symbol is available via ab simple_link -> go to this vertex
    if (current_vertex->next[current_symbol] != -1) {
      current_vertex = &data[current_vertex->next[current_symbol]];
      go_to_next_vertex = false;
    } else {
      // -> go to the suffix_links
      BlaBla(current_vertex, current_symbol);
    }

    // current_vertex is root and current_symbol is not in Trie -> skip
    if (current_vertex->prev == -1 &&
        current_vertex->next[current_symbol] == -1) {
      continue;
    }

    // current_symbol is available from current_vertex -> go to this vertex
    if (go_to_next_vertex && current_vertex->next[current_symbol] != -1) {
      current_vertex = &data[current_vertex->next[current_symbol]];
    }

    // current_vertex is terminal -> occurrence is found
    if (current_vertex->is_terminal) {
      for (int idx : current_vertex->word_idx) {
        occurrence[idx].push_back(static_cast<int>(i) -
                                  current_vertex->word_size + 1);
      }
    }

    // search for shorter occurrences -> go compressed_links
    int current_terminal_vertex_id = current_vertex->compressed_link;
    Something(current_terminal_vertex_id, i);
  }
}

void Trie::EditMatrix(std::vector<std::vector<int>>& matrix, int idx) {
  for (int i = 0; i < static_cast<int>(occurrence.size()); ++i) {
    for (int j = 0; j < static_cast<int>(occurrence[i].size()); ++j) {
      if (idx - i >= 0 && idx - i < static_cast<int>(matrix.size()) &&
          occurrence[i][j] < static_cast<int>(matrix[0].size())) {
        matrix[idx - i][occurrence[i][j]] += 1;
      }
    }
  }
}

void Trie::EditReverseMatrix(std::vector<std::vector<int>>& matrix, int idx) {
  for (int i = 0; i < static_cast<int>(occurrence.size()); ++i) {
    for (int j = 0; j < static_cast<int>(occurrence[i].size()); ++j) {
      if (idx - i >= 0 && (idx - i) < static_cast<int>(matrix[0].size()) &&
          occurrence[i][j] < static_cast<int>(matrix.size())) {
        matrix[occurrence[i][j]][idx - i] += 1;
      }
    }
  }
}

int main() {
  SpeedUp();
  int nb;
  int mb;
  std::cin >> nb >> mb;
  std::vector<std::string> table(nb);
  for (int i = 0; i < nb; ++i) {
    std::cin >> table[i];
  }
  std::vector<std::string> table_reverse(mb);
  for (int i = 0; i < mb; ++i) {
    for (int j = 0; j < nb; ++j) {
      table_reverse[i] += table[j][i];
    }
  }
  int ab;
  int bb;
  std::cin >> ab >> bb;
  std::vector<std::string> pattern(ab);
  for (int i = 0; i < ab; ++i) {
    std::cin >> pattern[i];
  }
  std::vector<std::string> pattern_reverse(bb);
  for (int i = 0; i < bb; ++i) {
    for (int j = 0; j < ab; ++j) {
      pattern_reverse[i] += pattern[j][i];
    }
  }
  std::vector<std::vector<int>> matrix(nb - ab + 1,
                                       std::vector<int>(mb - bb + 1, 0));

  Trie trie;
  for (const auto& word : pattern) {
    trie.AddWord(word);
  }
  trie.InitLinks();
  for (int i = 0; i < static_cast<int>(table.size()); ++i) {
    trie.SearchOccurrences(table[i]);
    trie.EditMatrix(matrix, i);
  }

  trie = Trie();
  for (const auto& word : pattern_reverse) {
    trie.AddWord(word);
  }
  trie.InitLinks();
  for (int i = 0; i < static_cast<int>(table_reverse.size()); ++i) {
    trie.SearchOccurrences(table_reverse[i]);
    trie.EditReverseMatrix(matrix, i);
  }

  int count = 0;
  for (auto& row : matrix) {
    for (int item : row) {
      count += static_cast<int>(item >= ab + bb - 2);
    }
  }
  std::cout << count;
}