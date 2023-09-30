// no_concepts
#include <iostream>
#include <queue>
#include <vector>

struct Vertex {
  static const int kSigma = 26;
  int prev;
  int idx;
  bool is_terminal;
  int link_symbol;
  int link = -1;
  int compressed_link = -1;
  std::vector<int> word_idx = std::vector<int>();
  int word_size = -1;
  std::vector<int> next = std::vector<int>(kSigma, -1);
};

struct Trie {
  std::vector<Vertex> data = std::vector<Vertex>(1, Vertex{-1, 0, false, -1});
  std::vector<std::vector<int>> occurrence;
  int count = -1;

  Vertex* GetRoot();
  void AddWord(const std::string& word);
  void InitLinks();
  void SearchOccurrences(const std::string& text);
  void PrintOccurrences();
};

Vertex* Trie::GetRoot() { return data.data(); }

void Trie::AddWord(const std::string& word) {
  Vertex* current_vertex = GetRoot();
  count++;
  occurrence.emplace_back();
  for (size_t i = 0; i < word.size(); ++i) {
    int current_symbol = word[i] - 'a';
    if (current_vertex->next[current_symbol] == -1) {
      current_vertex->next[current_symbol] = static_cast<int>(data.size());
      data.push_back(Vertex{current_vertex->idx, static_cast<int>(data.size()),
                            i == word.size() - 1, current_symbol});
      if (i == word.size() - 1) {
        data[data.size() - 1].word_idx.push_back(count);
        data[data.size() - 1].word_size = static_cast<int>(word.size());
      }
      current_vertex = &data[data.size() - 1];
      continue;
    }
    current_vertex = &data[current_vertex->next[word[i] - 'a']];
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

void Trie::SearchOccurrences(const std::string& text) {
  Vertex* current_vertex = GetRoot();
  for (size_t i = 0; i < text.size(); ++i) {
    bool go_to_next_vertex = true;
    int current_symbol = text[i] - 'a';
    // current_symbol is available via a simple_link -> go to this vertex
    if (current_vertex->next[current_symbol] != -1) {
      current_vertex = &data[current_vertex->next[current_symbol]];
      go_to_next_vertex = false;
    } else {
      // -> go to the suffix_links
      while (current_vertex->prev != -1 &&
             current_vertex->next[current_symbol] == -1) {
        current_vertex = &data[current_vertex->link];
      }
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
    while (current_terminal_vertex_id != -1) {
      if (data[current_terminal_vertex_id].is_terminal) {
        for (int idx : data[current_terminal_vertex_id].word_idx) {
          occurrence[idx].push_back(static_cast<int>(i) -
                                    data[current_terminal_vertex_id].word_size +
                                    1);
        }
      }
      current_terminal_vertex_id =
          data[current_terminal_vertex_id].compressed_link;
    }
  }
}

void Trie::PrintOccurrences() {
  for (auto& word_occurrence : occurrence) {
    std::cout << word_occurrence.size() << ' ';
    for (int idx : word_occurrence) {
      std::cout << idx + 1 << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::string text;
  int words_number;
  std::cin >> text;
  std::cin >> words_number;

  Trie trie;
  for (int i = 0; i < words_number; ++i) {
    std::string word;
    std::cin >> word;
    trie.AddWord(word);
  }
  trie.InitLinks();
  trie.SearchOccurrences(text);
  trie.PrintOccurrences();
}