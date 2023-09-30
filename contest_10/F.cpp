#include <iostream>
#include <unordered_set>

// NRVO no-copy
std::unordered_set<int64_t> HashCyclicString(std::string& str, int64_t base,
                                             int64_t mod) {
  std::unordered_set<int64_t> hash;

  // first calculation
  int64_t hash_val = str[0];
  int64_t max_base_degree = 1;
  for (int i = 1; i < static_cast<int>(str.size()); ++i) {
    hash_val *= base;
    hash_val += str[i];
    hash_val %= mod;

    max_base_degree *= base;
    max_base_degree %= mod;
  }
  hash.insert(hash_val);

  // calculate cyclic shift
  for (int i = 0; i < static_cast<int>(str.size()) - 1; ++i) {
    hash_val -= max_base_degree * str[i];
    hash_val *= base;
    hash_val += str[i];
    hash_val %= mod;
    hash.insert(hash_val);
  }

  return hash;
}

int64_t SearchCyclicString(std::string& text, std::string& pattern,
                           int64_t base, int64_t mod) {
  std::unordered_set<int64_t> hash = HashCyclicString(pattern, base, mod);
  int cnt = 0;

  int64_t hash_val = text[0];
  int64_t max_base_degree = 1;
  for (int i = 1; i < static_cast<int>(pattern.size()); ++i) {
    hash_val *= base;
    hash_val += text[i];
    hash_val %= mod;

    max_base_degree *= base;
    max_base_degree %= mod;
  }

  for (int i = 0; i < static_cast<int>(text.size()); ++i) {
    cnt += static_cast<int>(hash.contains(hash_val));

    if (i == static_cast<int>(text.size() - pattern.size())) {
      break;
    }
    hash_val -= max_base_degree * text[i];
    hash_val *= base;
    hash_val += text[i + pattern.size()];
    hash_val %= mod;
  }

  return cnt;
}

int main() {
  std::string text;
  std::string pattern;

  std::cin >> pattern >> text;

  const int64_t kBase = 1331;
  const int64_t kMod = 9223372036854775783;

  if (pattern.size() > text.size()) {
    std::cout << 0;
    return 0;
  }
  std::cout << SearchCyclicString(text, pattern, kBase, kMod);
}