#include <iostream>
#include <vector>

void SpeedUp() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
}

class HTable {
 public:
  HTable(long long number) {
    kBaseSize_ = number + (rand() % 127);
    table_ = new std::vector<long long>[kBaseSize_];
  }

  ~HTable() { delete[] table_; }

  int Find(int item) {
    int index = GetHash(item);
    int cur_size = table_[index].size();

    for (int i = 0; i < cur_size; ++i) {
      if (table_[index][i] == item) {
        return i;
      }
    }
    return -1;
  }

  void Insert(int item) {
    int index = GetHash(item);
    table_[index].push_back(item);
  }

  void Delete(int item) {
    int inner_index = Find(item);
    if (inner_index != -1) {
      int index = GetHash(item);
      int cur_size = table_[index].size();

      int temp = table_[index][cur_size - 1];
      table_[index][cur_size - 1] = table_[index][inner_index];
      table_[index][inner_index] = temp;

      table_[index].pop_back();
    }
  }

 private:
  long long kBaseSize_;
  static const long long kBaseFactor = 31;
  static const long long kBaseAdd = 1913;
  std::vector<long long>* table_;

  int GetHash(int item) {
    return (int)((kBaseFactor * item + kBaseAdd) % kBaseSize_);
  }
};

int main() {
  SpeedUp();

  int n;
  long long x;
  std::vector<long long> ans;

  std::cin >> n;
  HTable h_table(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    h_table.Insert(x);
  }

  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> x;
    if (h_table.Find(x) != -1) {
      ans.push_back(x);
      h_table.Delete(x);
    }
  }

  int size = static_cast<int>(ans.size());
  std::cout << size << '\n';
  for (int i = 0; i < size; ++i) {
    std::cout << ans[i] << ' ';
  }
}