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

void Merge(std::string& result_str, std::string& other_str) {
  std::string merge_str;
  if (result_str.size() >= other_str.size()) {
    merge_str = other_str;
    merge_str += '#';
    merge_str += result_str.substr(result_str.size() - other_str.size(),
                                   other_str.size());
  } else {
    merge_str = other_str.substr(0, result_str.size());
    merge_str += '#';
    merge_str += result_str;
  }
  std::vector<int> pref = PrefixFunction(merge_str);
  result_str += other_str.substr(pref[pref.size() - 1],
                                 other_str.size() - pref[pref.size() - 1]);
}

int main() {
  int number;
  std::cin >> number;
  std::string result_str;
  std::string other_str;
  std::cin >> result_str;
  for (int i = 1; i < number; ++i) {
    std::cin >> other_str;
    Merge(result_str, other_str);
  }
  std::cout << result_str;
}