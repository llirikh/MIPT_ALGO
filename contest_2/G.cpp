#include <iostream>

void SpeedUp() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
}

void Equalize(std::string* array, int number, int size) {
  for (int i = 0; i < number; i++) {
    array[i] = std::string(size - array[i].size(), '0') + array[i];
  }
}

void CountSort(std::string* array, int number, int discharge) {
  int cnt[10] = {};
  for (int i = 0; i < number; i++) {
    cnt[array[i][discharge] - '0']++;
  }
  for (int i = 1; i < 10; i++) {
    cnt[i] += cnt[i - 1];
  }

  std::string* sub_array = new std::string[number];
  for (int i = number - 1; i >= 0; i--) {
    sub_array[cnt[array[i][discharge] - '0'] - 1] = array[i];
    cnt[array[i][discharge] - '0']--;
  }
  for (int i = 0; i < number; i++) {
    array[i] = sub_array[i];
  }

  delete[] sub_array;
}

void Print(std::string& string) {
  int zero_count = 0;
  while (string[zero_count] == '0') {
    zero_count++;
  }
  for (int i = zero_count; i < (int)string.size(); i++) {
    std::cout << string[i];
  }
  std::cout << '\n';
}

int main() {
  SpeedUp();

  int number;
  std::cin >> number;
  std::string* array = new std::string[number];

  int size = 0;
  for (int i = 0; i < number; i++) {
    std::cin >> array[i];
    size = std::max(size, static_cast<int>(array[i].size()));
  }
  Equalize(array, number, size);

  for (int i = size - 1; i >= 0; i--) {
    CountSort(array, number, i);
  }

  for (int i = 0; i < number; i++) {
    Print(array[i]);
  }

  delete[] array;

  return 0;
}