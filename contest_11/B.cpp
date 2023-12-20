#include <iostream>
#include <stack>
#include <vector>

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

std::vector<int> GetLCP(std::string& str, std::vector<int>& suffix_array) {
  std::vector<int> permutation(suffix_array.size());
  for (int i = 0; i < static_cast<int>(suffix_array.size()); ++i) {
    permutation[suffix_array[i]] = i;
  }
  std::vector<int> lcp(suffix_array.size());
  int kk = 0;
  for (int i = 0; i < static_cast<int>(permutation.size()) - 1; ++i) {
    int idx = permutation[i];
    int idx1 = suffix_array[idx];
    int idx2 = suffix_array[idx - 1];

    int size = static_cast<int>(str.size());

    while (idx1 + kk < size && idx2 + kk < size &&
           str[idx1 + kk] == str[idx2 + kk]) {
      ++kk;
    }
    lcp[idx] = kk;
    kk = std::max(0, kk - 1);
  }
  return lcp;
}

void Solve(std::vector<int>& histogram, std::vector<int>& suffix_array,
           std::string& str) {
  std::stack<int> stack;
  stack.push(-1);
  int area = histogram[0];
  int idx = 0;
  int size = static_cast<int>(histogram.size());
  std::vector<int> left_smaller(size, -1);
  std::vector<int> right_smaller(size, size);
  while (idx < size) {
    while (!stack.empty() && stack.top() != -1 &&
           histogram[stack.top()] > histogram[idx]) {
      right_smaller[stack.top()] = idx;
      stack.pop();
    }
    if (idx > 0 && histogram[idx] == histogram[idx - 1]) {
      left_smaller[idx] = left_smaller[idx - 1];
    } else {
      left_smaller[idx] = stack.top();
    }
    stack.push(idx);
    idx++;
  }
  idx = 0;
  for (int j = 0; j < size; j++) {
    int new_area = histogram[j] * (right_smaller[j] - left_smaller[j] - 1);
    if (new_area > area) {
      idx = j;
      area = new_area;
    }
  }
  if (area == 0) {
    std::cout << 1 << '\n';
    std::cout << 1 << '\n';
    std::cout << str[0] - 'a' + 1;
  } else {
    std::cout << area << '\n';
    std::cout << histogram[idx] << '\n';
    for (int i = 0; i < histogram[idx]; ++i) {
      std::cout << str[suffix_array[idx] + i] - 'a' + 1 << ' ';
    }
  }
}

int main() {
  int nn = 0;
  int mm = 0;
  std::string str;
  std::cin >> nn >> mm;
  for (int i = 0; i < nn; ++i) {
    int symbol = 0;
    std::cin >> symbol;
    str += char(symbol + 'a' - 1);
  }
  str += '`';

  auto suffix_array = GetSuffixArray(str, '`', 'k');
  auto lcp = GetLCP(str, suffix_array);

  std::vector<int> histogram(lcp.size());
  for (int i = 1; i < static_cast<int>(lcp.size()); ++i) {
    histogram[i] = lcp[i];
    histogram[i - 1] = std::max(histogram[i - 1], histogram[i]);
  }

  Solve(histogram, suffix_array, str);

  return 0;
}