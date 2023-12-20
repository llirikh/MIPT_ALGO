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

std::vector<int> GetLCP(std::string& str, std::vector<int>& suffix_array) {
  std::vector<int> permutation(suffix_array.size());
  for (int i = 0; i < suffix_array.size(); ++i) {
    permutation[suffix_array[i]] = i;
  }

  std::vector<int> lcp(suffix_array.size());
  int k = 0;
  for (int i = 0; i < permutation.size() - 1; ++i) {
    int idx = permutation[i];
    int idx1 = suffix_array[idx];
    int idx2 = suffix_array[idx - 1];

    while (idx1 + k < str.size() && idx2 + k < str.size() && str[idx1 + k] == str[idx2 + k]) {
      ++k;
    }
    lcp[idx] = k;
    k = std::max(0, k - 1);
  }

  return lcp;
}

int Solve(std::vector<int>& hystogram) {
  stack<int> s;

  int max_area = 0; // Initialize max area
  int tp; // To store top of stack
  int area_with_top; // To store area with top bar
                     // as the smallest bar

  // Run through all bars of given histogram
  int i = 0;
  while (i < n) {
    // If this bar is higher than the bar on top
    // stack, push it to stack
    if (s.empty() || hist[s.top()] <= hist[i])
      s.push(i++);

    // If this bar is lower than top of stack,
    // then calculate area of rectangle with stack
    // top as the smallest (or minimum height) bar.
    // 'i' is 'right index' for the top and element
    // before top in stack is 'left index'
    else {
      tp = s.top(); // store the top index
      s.pop(); // pop the top

      // Calculate the area with hist[tp] stack
      // as smallest bar
      area_with_top
          = hist[tp]
            * (s.empty() ? i : i - s.top() - 1);

      // update max area, if needed
      if (max_area < area_with_top)
        max_area = area_with_top;
    }
  }

  // Now pop the remaining bars from stack and calculate
  // area with every popped bar as the smallest bar
  while (s.empty() == false) {
    tp = s.top();
    s.pop();
    area_with_top
        = hist[tp] * (s.empty() ? i : i - s.top() - 1);

    if (max_area < area_with_top)
      max_area = area_with_top;
  }

  return max_area;
}

int main() {
  std::string str;
  std::cin >> str;
  str += '`';
  auto suffix_array = GetSuffixArray(str, '`', 'z');
  auto lcp = GetLCP(str, suffix_array);

  std::vector<int> hystogram(lcp.size());
  for (int i = 1; i < lcp.size(); ++i) {
    hystogram[i] = lcp[i];
    hystogram[i - 1] = std::max(hystogram[i - 1], hystogram[i]);
  }



  return 0;
}