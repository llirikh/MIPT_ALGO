#include <iostream>
#include <vector>

// NRVO (without copies)
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
  std::string s;
  std::cin >> s;

  std::vector<int> pref = PrefixFunction(s);
  for (int i = 1; i < pref.size(); ++i) {
    std::cout << pref[i] << ' ';
  }
}