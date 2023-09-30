#include <iostream>
#include <vector>

long long modulo = 1073741825;

int Bit(int i, int mask) { return static_cast<int>(((mask >> i) & 1) != 0); }

int Check(int a, int b, int m) {
  for (int i = 0; i < m - 1; ++i) {
    int sum = Bit(i, a) + Bit(i, b) + Bit(i + 1, a) + Bit(i + 1, b);
    if (sum == 0 || sum == 4) {
      return 0;
    }
  }
  return 1;
}

enum MatrixType { ZERO, UNIT, SPECIAL };

struct Matrix {
  int height{0};
  int width{0};
  std::vector<std::vector<long long>> matrix;

  Matrix() = default;
  Matrix(int height, int width);
  Matrix(int dimension, MatrixType type);

  long long Sum();
};

Matrix::Matrix(int height, int width) : height(height), width(width) {
  for (int i = 0; i < height; ++i) {
    matrix.emplace_back();
    for (int j = 0; j < width; ++j) {
      matrix[i].push_back(0);
    }
  }
}

Matrix::Matrix(int dimension, MatrixType type) : height(dimension), width(dimension) {
  if (type == SPECIAL) {
    height = 1 << dimension;
    width = 1 << dimension;
  }
  for (int i = 0; i < height; ++i) {
    matrix.emplace_back();
    for (int j = 0; j < width; ++j) {
      matrix[i].push_back(0);
      if (type == UNIT && i == j) {
        matrix[i][j] = 1;
      }
      if (type == SPECIAL) {
        matrix[i][j] = Check(i, j, dimension);
      }
    }
  }
}

long long Matrix::Sum() {
  long long sum = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      sum += matrix[i][j];
      sum %= modulo;
    }
  }
  return sum;
}

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

unsigned long Pow(unsigned long num, unsigned long degree) {
  unsigned long r = 1;
  for (int id = 31; id >= 0; id--) {
    if ((degree & (1 << id)) != 0u) {
      r = (r * num) % modulo;
    }
    if (id != 0) {
      r = (r * r) % modulo;
    }
  }
  return r;
}

void Print(Matrix& matrix) {
  for (int i = 0; i < matrix.height; ++i) {
    for (int j = 0; j < matrix.width; ++j) {
      std::cout << matrix.matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}