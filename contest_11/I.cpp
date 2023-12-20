#include <iostream>
#include <vector>

void Println(std::vector<int>& vector) {
  for (auto item : vector) {
    std::cout << item << ' ';
  }
  std::cout << '\n';
}

int InitSuffixArray(std::string& string, char min_symbol, char max_symbol,
                    std::vector<int>& suffix_array,
                    std::vector<int>& class_array) {
  std::vector<int> count(max_symbol - min_symbol + 1, 0);
  // init suffix_array by count_sort
  for (auto symbol : string) {
    ++count[symbol - min_symbol];
  }
  for (int i = 1; i < static_cast<int>(count.size()); ++i) {
    count[i] += count[i - 1];
  }
  for (int i = static_cast<int>(string.size()) - 1; i >= 0; --i) {
    suffix_array[--count[string[i] - min_symbol]] = i;
  }

  // init class_array
  int max = 0;
  class_array[suffix_array[0]] = 0;
  for (size_t i = 1; i < suffix_array.size(); ++i) {
    class_array[suffix_array[i]] = class_array[suffix_array[i - 1]];
    if (string[suffix_array[i]] != string[suffix_array[i - 1]]) {
      ++class_array[suffix_array[i]];
    }
    if (class_array[suffix_array[i]] > max) {
      max = class_array[suffix_array[i]];
    }
  }
  return max;
}

std::vector<int> GetSuffixArray(std::string& string, char min_symbol,
                                char max_symbol) {
  int size = static_cast<int>(string.size());
  std::vector<int> suffix_array(size);
  std::vector<int> class_array(size);

  int max = InitSuffixArray(string, min_symbol, max_symbol, suffix_array,
                            class_array);
  if (max == size - 1) {
    return suffix_array;
  }

  std::vector<int> count(size, 0);
  std::vector<int> new_suffix_array(size);
  std::vector<int> new_class_array(size);
  int degree = 0;
  while ((1 << degree) <= string.size()) {
    // renew suffix_array by count_sort
    for (int i = 0; i < size; ++i) {
      new_suffix_array[i] = suffix_array[i] - (1 << degree);
      if (new_suffix_array[i] < 0) {
        new_suffix_array[i] += size;
      }
    }

    std::fill(count.begin(), count.end(), 0);
    for (auto item : new_suffix_array) {
      ++count[class_array[item]];
    }
    for (int i = 1; i < size; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; --i) {
      suffix_array[--count[class_array[new_suffix_array[i]]]] =
          new_suffix_array[i];
    }

    // renew class_array
    new_class_array[suffix_array[0]] = 0;
    for (int i = 1; i < size; ++i) {
      new_class_array[suffix_array[i]] = new_class_array[suffix_array[i - 1]];
      if (class_array[suffix_array[i]] != class_array[suffix_array[i - 1]] ||
          class_array[(suffix_array[i] + (1 << degree)) % size] !=
              class_array[(suffix_array[i - 1] + (1 << degree)) % size]) {
        ++new_class_array[suffix_array[i]];
      }
      if (new_class_array[suffix_array[i]] == size - 1) {
        return suffix_array;
      }
    }
    class_array = new_class_array;

    ++degree;
  }

  return suffix_array;
}

int main() {
  std::string str;
  std::cin >> str;
  str += '`';
  auto suffix_array = GetSuffixArray(str, '`', 'z');

  std::vector<int> permutation(str.size());
  for (int i = 0; i < str.size(); ++i) {
    permutation[suffix_array[i]] = i;
  }

  for (auto item : permutation) {
    std::cout << item << ' ';
  }

  std::vector<int> l(str.size());

}