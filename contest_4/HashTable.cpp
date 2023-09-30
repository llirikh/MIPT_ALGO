#include <vector>

class HashTable {
 public:
  HashTable(int number);
  ~HashTable();

  int Find(int item);
  void Insert(int item);
  void Delete(int item);

 private:
  int BaseSize_;
  static const int kBaseFactor = 31;
  static const int kBaseAdd = 1913;
  std::vector<int>* table_;

  int GetHash(int item);
};

HashTable::HashTable(int number) {
  BaseSize_ = number + 37;
  table_ = new std::vector<int>[BaseSize_];
}

HashTable::~HashTable() { delete[] table_; }

int HashTable::Find(int item) {
  int index = GetHash(item);
  int current_size = table_[index].size();

  for (int i = 0; i < current_size; ++i) {
    if (table_[index][i] == item) {
      return i;
    }
  }
  return -1;
}

void HashTable::Insert(int item) {
  if (Find(item) == -1) {
    int index = GetHash(item);
    table_[index].push_back(item);
  }
}

void HashTable::Delete(int item) {
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

int HashTable::GetHash(int item) {
  return ((kBaseFactor * item + kBaseAdd) % BaseSize_);
}