#include <iostream>
#include <list>
#include <numeric>
#include <vector>

static const int kAlphabetSize = 26;

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

std::string EncodeBWT(std::string& string) {
  auto suffix_array = GetSuffixArray(string, 'a', 'z');
  std::string result;
  for (int item : suffix_array) {
    result += string[(item + string.size() - 1) % string.size()];
  }
  return result;
}

std::string DecodeBWT(std::string& string, int original_position) {
  std::vector<int> count(kAlphabetSize, 0);
  for (char symbol : string) {
    ++count[symbol - 'a'];
  }
  int sum = 0;
  for (int i = 0; i < kAlphabetSize; ++i) {
    sum += count[i];
    count[i] = sum - count[i];
  }
  std::vector<int> table(string.size());
  for (int i = 0; i < static_cast<int>(string.size()); ++i) {
    table[count[string[i] - 'a']] = i;
    ++count[string[i] - 'a'];
  }
  int reverse_position = table[original_position];
  std::string result;
  for (int i = 0; i < static_cast<int>(string.size()); ++i) {
    result += string[reverse_position];
    reverse_position = table[reverse_position];
  }
  return result;
}

std::string EncodeMTF(std::string& string) {
  std::list<char> alphabet;
  for (int i = 0; i < kAlphabetSize; ++i) {
    alphabet.push_back(char('a' + i));
  }

  std::string result;
  for (char symbol : string) {
    int idx = 0;
    auto iterator = alphabet.begin();
    while (*iterator != symbol) {
      iterator++;
      ++idx;
    }
    result += char(idx + 'a');
    alphabet.erase(iterator);
    alphabet.push_front(symbol);
  }
  return result;
}

std::string DecodeMTF(std::string& string) {
  std::list<char> alphabet;
  for (int i = 0; i < kAlphabetSize; ++i) {
    alphabet.push_back(char('a' + i));
  }

  std::string result;
  for (char symbol : string) {
    auto iterator = alphabet.begin();
    int idx = 0;
    while (idx != symbol - 'a') {
      iterator++;
      idx++;
    }
    result += *iterator;
    alphabet.erase(iterator);
    alphabet.push_front(result[result.size() - 1]);
  }
  return result;
}

std::string EncodeRLE(std::string& string) {
  std::string result;

  int count = 1;
  for (int i = 1; i < static_cast<int>(string.size()); ++i) {
    if (string[i] == string[i - 1]) {
      ++count;
    } else {
      result += string[i - 1] + std::to_string(count);
      count = 1;
    }
  }
  result += string[string.size() - 1] + std::to_string(count);
  return result;
}

std::string DecodeRLE(std::string& string) {
  std::string result;

  int idx = 0;
  while (idx < static_cast<int>(string.size())) {
    char symbol = string[idx];
    ++idx;
    std::string number_string;
    while (idx < static_cast<int>(string.size()) && '0' <= string[idx] &&
           string[idx] <= '9') {
      number_string += string[idx];
      ++idx;
    }
    for (int i = 0; i < std::stoi(number_string); ++i) {
      result += symbol;
    }
  }

  return result;
}

int main() {
  int type;
  std::string string;
  std::cin >> type >> string;
  if (type == 1) {
    string = EncodeBWT(string);
    string = EncodeMTF(string);
    string = EncodeRLE(string);
  } else {
    string = DecodeRLE(string);
    string = DecodeMTF(string);
    int original_position;
    std::cin >> original_position;
    string = DecodeBWT(string, original_position);
  }
  std::cout << string;
}