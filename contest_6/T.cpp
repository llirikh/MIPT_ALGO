#include <iostream>
#include <vector>

enum MatrixType { ZERO, UNIT, SPECIAL };

struct Matrix {
  int height{0};
  int width{0};
  std::vector<std::vector<long long>> matrix;

  Matrix() = default;
  Matrix(int height, int width) : height(height), width(width) {
    for (int i = 0; i < height; ++i) {
      matrix.emplace_back();
      for (int j = 0; j < width; ++j) {
        matrix[i].push_back(0);
      }
    }
  }
  Matrix(int dimension, MatrixType type) : height(dimension), width(dimension) {
    for (int i = 0; i < height; ++i) {
      matrix.emplace_back();
      for (int j = 0; j < width; ++j) {
        matrix[i].push_back(0);
        if (type == UNIT && i == j) {
          matrix[i][j] = 1;
        }
        if (type == SPECIAL) {
          matrix[i][j] = static_cast<long long>(abs(i - j) <= 1);
        }
      }
    }
  }

  Matrix(int height, Matrix& matrix) : height(height), width(1) {
    for (int i = 0; i < height; ++i) {
      this->matrix.emplace_back();
      if (this->height - i > matrix.height) {
        this->matrix[i].push_back(0);
      } else {
        this->matrix[i].push_back(
            matrix.matrix[matrix.height - this->height + i][0]);
      }
    }
  }
};

Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
  const long long kModulo = 1e9 + 7;
  Matrix result;
  for (int i = 0; i < lhs.height; ++i) {
    result.matrix.emplace_back();
    for (int j = 0; j < rhs.width; ++j) {
      result.matrix[i].push_back(0);
      for (int k = 0; k < lhs.width; ++k) {
        long long multiplication =
            (lhs.matrix[i][k] * rhs.matrix[k][j] + kModulo) % kModulo;
        result.matrix[i][j] += multiplication;
        result.matrix[i][j] %= kModulo;
      }
    }
  }
  result.height = lhs.height;
  result.width = rhs.width;
  return result;
}

Matrix Pow(Matrix matrix, long long degree) {
  Matrix result(matrix.height, UNIT);
  while (degree != 0) {
    if ((degree & 1) != 0) {
      result = result * matrix;
    }
    matrix = matrix * matrix;
    degree >>= 1;
  }
  return result;
}

int main() {
  long long n, k;
  std::cin >> n >> k;

  Matrix a(1, 1);
  a.matrix[0][0] = 1;
  for (int i = 0; i < n; ++i) {
    long long x1, x2;
    int y;
    std::cin >> x1 >> x2 >> y;
    x2 = std::min(x2, k);

    Matrix new_a(y + 1, a);
    a = new_a;
    Matrix t(y + 1, SPECIAL);
    a = Pow(t, x2 - x1) * a;
  }

  std::cout << a.matrix[a.height - 1][0];
}
