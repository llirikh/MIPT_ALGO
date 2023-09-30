#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

void Recode(std::string& s) {
  int cnt = 0;
  std::unordered_map<char, char> used;
  for (int i = 0; i < (int)s.length(); ++i) {
    if (used.find(s[i]) != used.end()) {
      s[i] = used[s[i]];
    } else {
      used[s[i]] = (char)('a' + cnt);
      s[i] = (char)('a' + cnt);
      cnt++;
    }
  }
}

int main() {
  SpeedUp();
  int n;
  std::cin >> n;
  std::unordered_map<std::string, int> map;
  for (int i = 0; i < n; ++i) {
    char symbol;
    std::string s;
    std::cin >> symbol >> s;
    Recode(s);
    if (symbol == '?') {
      if (map.find(s) == map.end()) {
        std::cout << "NO" << '\n';
      } else {
        std::cout << "YES" << '\n';
      }
    } else {
      ++map[s];
    }
  }
}