#include <iostream>
#include <vector>

void StableCountSort(std::vector<int>& array, int max_value, std::vector<int>& result) {
  std::vector<int> count(max_value + 1);
  for (auto& item : array) {
    ++count[item];
  }
  for (int i = 1; i < count.size(); ++i) {
    count[i] += count[i - 1];
  }

  for (int i = static_cast<int>(array.size()) - 1; i >= 0; --i) {
    result[--count[array[i]]] = array[i];
  }
}


int main() {
  std::vector<int> example{3, 2, 1, 5, 6, 3, 5, 1, 2, 1};
  std::vector<int> result(example.size());

  StableCountSort(example, 10, result);

  for (auto& item : example) {
    std::cout << item << ' ';
  }
  std::cout << '\n';
  for (auto& item : result) {
    std::cout << item << ' ';
  }
}