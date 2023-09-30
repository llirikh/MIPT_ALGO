#include <iostream>
#include <vector>

class HashTable {
 public:
  HashTable(int number) {
    BaseSize_ = number + 37;
    table_ = new std::vector<int>[BaseSize_];
  }

  ~HashTable() { delete[] table_; }

  int Find(int item) {
    int index = GetHash(item);
    int current_size = table_[index].size();

    for (int i = 0; i < current_size; ++i) {
      if (table_[index][i] == item) {
        return i;
      }
    }
    return -1;
  }

  void Insert(int item) {
    if (Find(item) == -1) {
      int index = GetHash(item);
      table_[index].push_back(item);
    }
  }

  void Delete(int item) {
    int inner_index = Find(item);
    if (inner_index != -1) {
      int index = GetHash(item);
      int current_size = table_[index].size();

      int temporary = table_[index][current_size - 1];
      table_[index][current_size - 1] = table_[index][inner_index];
      table_[index][inner_index] = temporary;

      table_[index].pop_back();
    }
  }

 private:
  int BaseSize_;
  static const int kBaseFactor = 31;
  static const int kBaseAdd = 1913;
  std::vector<int>* table_;

  int GetHash(int item) {
    return ((kBaseFactor * item + kBaseAdd) % BaseSize_);
  }
};

int main() {
  int number;
  std::cin >> number;

  HashTable hash_table(number);

  char request_type;
  int item;

  for (int i = 0; i < number; ++i) {
    std::cin >> request_type >> item;

    if (request_type == '+') {
      hash_table.Insert(item);
    }
    if (request_type == '-') {
      hash_table.Delete(item);
    }
    if (request_type == '?') {
      int is_in_table = hash_table.Find(item);
      if (is_in_table != -1) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
  }

  return 0;
}