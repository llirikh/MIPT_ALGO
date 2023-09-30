// clang-tidy off
// clang-format off
#include <iostream>
#include <vector>

const int kInf = 30000;
int nq;

int main() {
  std::cin >> nq;
  std::vector<std::vector<int>> matrix(nq, std::vector<int>(nq, kInf));
  for (int i = 0; i < nq; ++i) {
    for (int j = 0; j < nq; ++j) {
      std::cin >> matrix[i][j];
      matrix[i][j] = matrix[i][j] == 0 ? kInf : matrix[i][j];
    }
  }
  for (int k = 0; k < nq; ++k) {
    for (int i = 0; i < nq; ++i) {
      for (int j = 0; j < nq; ++j) {
        if (matrix[i][k] != kInf && matrix[k][j] != kInf) {
          matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
          matrix[i][j] = matrix[i][j] < kInf ? 1 : kInf;
        }
      }
    }
  }
  for (int i = 0; i < nq; ++i) {
    for (int j = 0; j < nq; ++j) {
       std::cout << (matrix[i][j] == kInf ? 0 : 1) << ' ';
    }
    std::cout << '\n';
  }
}
// clang-tidy on
// clang-format on