#include <iostream>
#include <vector>

std::vector<int> PrefixFunction(std::string& str) {
  std::vector<int> pref(str.size() + 1);
  pref[0] = -1;
  for (size_t i = 0; i < str.size(); ++i) {
    int last_pref_pos = pref[i];
    while (last_pref_pos != -1 && str[i] != str[last_pref_pos]) {
      last_pref_pos = pref[last_pref_pos];
    }
    pref[i + 1] = last_pref_pos + 1;
  }
  return pref;
}

int main() {
  std::string str;
  std::getline(std::cin, str);

  int ans = 1;
  for (int i = 0; i < static_cast<int>(str.size()); ++i) {
    std::string string = str.substr(i, str.size() - i);
    std::vector<int> pref = PrefixFunction(string);
    for (int j = 0; j < static_cast<int>(string.size()); ++j) {
      if (pref[j + 1] != 0 && pref[j - pref[j + 1] + 2] == 1) {
        ans = std::max(ans, (j + 1) / (j - pref[j + 1] + 1));
      }
    }
  }

  std::cout << ans;
}