// clang-format off
#pragma GCC target("avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("no-stack-protector")

#include <iostream>
#include <string>
#include <vector>

class BigInteger {
 public:
  BigInteger();
  BigInteger(std::string str);
  BigInteger(signed int i);
  BigInteger(unsigned int i);
  BigInteger(signed long long l);
  BigInteger(unsigned long long l);
  const BigInteger operator+() const;
  const BigInteger operator-() const;
  const BigInteger operator++();
  const BigInteger operator++(int);
  const BigInteger operator--();
  const BigInteger operator--(int);
  friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
  friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
  friend const BigInteger operator+(BigInteger lhs, const BigInteger& rhs);
  BigInteger& operator+=(const BigInteger& num);
  friend const BigInteger operator-(BigInteger lhs, const BigInteger& rhs);
  BigInteger& operator-=(const BigInteger& num);
  friend const BigInteger operator*(const BigInteger& lhs,
                                    const BigInteger& rhs);
  BigInteger& operator*=(const BigInteger& num);
  friend const BigInteger operator/(const BigInteger& lhs,
                                    const BigInteger& rhs);
  BigInteger& operator/=(const BigInteger& num);
  bool Odd() const;
 private:
  static const int kBase = 1000000000;
  std::vector<int> digits_;
  bool is_negative_;
  void RemoveLeadingZeros();
  void ShiftRight();
};

BigInteger::BigInteger() { this->is_negative_ = false; }

BigInteger::BigInteger(std::string str) {
  if (str.length() == 0) {
    this->is_negative_ = false;
  } else {
    if (str[0] == '-') {
      str = str.substr(1);
      this->is_negative_ = true;
    } else {
      this->is_negative_ = false;
    }
    for (long long i = str.length(); i > 0; i -= 9) {
      if (i < 9) {
        this->digits_.push_back(atoi(str.substr(0, i).c_str()));
      } else {
        this->digits_.push_back(atoi(str.substr(i - 9, 9).c_str()));
      }
    }

    this->RemoveLeadingZeros();
  }
}

void BigInteger::RemoveLeadingZeros() {
  while (this->digits_.size() > 1 && this->digits_.back() == 0) {
    this->digits_.pop_back();
  }

  if (this->digits_.size() == 1 && this->digits_[0] == 0) {
    this->is_negative_ = false;
  }
}

bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs.is_negative_ != rhs.is_negative_) {
    return false;
  }
  if (lhs.digits_.empty()) {
    return rhs.digits_.empty() || (rhs.digits_.size() == 1 && rhs.digits_[0] == 0);
  }

  if (rhs.digits_.empty()) {
    return lhs.digits_.size() == 1 && lhs.digits_[0] == 0;
  }

  if (lhs.digits_.size() != rhs.digits_.size()) {
    return false;
  }

  for (size_t i = 0; i < lhs.digits_.size(); ++i) {
    if (lhs.digits_[i] != rhs.digits_[i]) {
      return false;
    }
  }

  return true;
}

const BigInteger BigInteger::operator+() const {
  return BigInteger(*this);
}

const BigInteger BigInteger::operator-() const {
  BigInteger copy(*this);
  copy.is_negative_ = !copy.is_negative_;
  return copy;
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
  if (lhs == rhs) {
    return false;
  }
  if (lhs.is_negative_) {
    if (rhs.is_negative_) {
      return ((-rhs) < (-lhs));
    }
    return true;
  }
  if (rhs.is_negative_) {
    return false;
  }
  if (lhs.digits_.size() != rhs.digits_.size()) {
    return lhs.digits_.size() < rhs.digits_.size();
  }
  for (long long i = lhs.digits_.size() - 1; i >= 0; --i) {
    if (lhs.digits_[i] != rhs.digits_[i]) {
      return lhs.digits_[i] < rhs.digits_[i];
    }
  }
  return false;
}

bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs == rhs);
}

bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
  return (lhs < rhs || lhs == rhs);
}

bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs <= rhs);
}

bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
  return !(lhs < rhs);
}

const BigInteger operator+(BigInteger lhs, const BigInteger& rhs) {
  if (lhs.is_negative_) {
    if (rhs.is_negative_) {
      return -(-lhs + (-rhs));
    }
    return rhs - (-lhs);
  }
  if (rhs.is_negative_) {
    return lhs - (-rhs);
  }
  int carry = 0;
  for (size_t i = 0; i < std::max(lhs.digits_.size(), rhs.digits_.size()) || carry != 0; ++i) {
    if (i == lhs.digits_.size()) {
      lhs.digits_.push_back(0);
    }
    lhs.digits_[i] += carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
    carry = static_cast<int>(lhs.digits_[i] >= BigInteger::kBase);
    if (carry != 0) {
      lhs.digits_[i] -= BigInteger::kBase;
    }
  }

  return lhs;
}

BigInteger& BigInteger::operator+=(const BigInteger& num) {
  return *this = (*this + num);
}

const BigInteger BigInteger::operator++() {
  return (*this += 1);
}

BigInteger::BigInteger(signed int i) {
  if (i < 0) {
    this->is_negative_ = true;
  } else {
    this->is_negative_ = false;
  }
  this->digits_.push_back(std::abs(i) % BigInteger::kBase);
  i /= BigInteger::kBase;
  if (i != 0) {
    this->digits_.push_back(std::abs(i));
  }
}

BigInteger::BigInteger(unsigned int i) {
  this->digits_.push_back(i % BigInteger::kBase);
  i /= BigInteger::kBase;
  if (i != 0) {
    this->digits_.push_back(i);
  }
}

BigInteger::BigInteger(signed long long l) {
  if (l < 0) {
    this->is_negative_ = true; l = -l;
  } else {
    this->is_negative_ = false;
  }
  do {
    this->digits_.push_back(l % BigInteger::kBase);
    l /= BigInteger::kBase;
  } while (l != 0);
}

BigInteger::BigInteger(unsigned long long l) {
  this->is_negative_ = false;
  do {
    this->digits_.push_back(l % BigInteger::kBase);
    l /= BigInteger::kBase;
  } while (l != 0);
}

const BigInteger BigInteger::operator++(int) {
  *this += 1;
  return *this - 1;
}

const BigInteger BigInteger::operator--() {
  return *this -= 1;
}

const BigInteger BigInteger::operator--(int) {
  *this -= 1;
  return *this + 1;
}

const BigInteger operator-(BigInteger lhs, const BigInteger& rhs) {
  if (rhs.is_negative_) {
    return lhs + (-rhs);
  }
  if (lhs.is_negative_) {
    return -(-lhs + rhs);
  }
  if (lhs < rhs) {
    return -(rhs - lhs);
  }
  int carry = 0;
  for (size_t i = 0; i < rhs.digits_.size() || carry != 0; ++i) {
    lhs.digits_[i] -= carry + (i < rhs.digits_.size() ? rhs.digits_[i] : 0);
    carry = static_cast<int>(lhs.digits_[i] < 0);
    if (carry != 0) {
      lhs.digits_[i] += BigInteger::kBase;
    }
  }

  lhs.RemoveLeadingZeros();
  return lhs;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
  return *this = (*this - num);
}

const BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
  BigInteger result;
  result.digits_.resize(lhs.digits_.size() + rhs.digits_.size());
  for (size_t i = 0; i < lhs.digits_.size(); ++i) {
    int carry = 0;
    for (size_t j = 0; j < rhs.digits_.size() || carry != 0; ++j) {
      long long cur = result.digits_[i + j] +
          lhs.digits_[i] * 1LL * (j < rhs.digits_.size() ? rhs.digits_[j] : 0) + carry;
      result.digits_[i + j] = static_cast<int>(cur % BigInteger::kBase);
      carry = static_cast<int>(cur / BigInteger::kBase);
    }
  }

  result.is_negative_ = lhs.is_negative_ != rhs.is_negative_;
  result.RemoveLeadingZeros();
  return result;
}

BigInteger& BigInteger::operator*=(const BigInteger& num) {
  return *this = (*this * num);
}

void BigInteger::ShiftRight() {
  if (this->digits_.empty()) {
    this->digits_.push_back(0);
    return;
  }
  this->digits_.push_back(this->digits_[this->digits_.size() - 1]);
  for (size_t i = this->digits_.size() - 2; i > 0; --i) {
    this->digits_[i] = this->digits_[i - 1];
  }
  this->digits_[0] = 0;
}

const BigInteger operator/(const BigInteger& lhs, const BigInteger& rhs) {
  BigInteger b = rhs;
  b.is_negative_ = false;
  BigInteger result, current;
  result.digits_.resize(lhs.digits_.size());
  for (long long i = static_cast<long long>(lhs.digits_.size()) - 1; i >= 0; --i) {
    current.ShiftRight();
    current.digits_[0] = lhs.digits_[i];
    current.RemoveLeadingZeros();
    int x = 0, l = 0, r = BigInteger::kBase;
    while (l <= r) {
      int m = (l + r) / 2;
      BigInteger t = b * m;
      if (t <= current) {
        x = m;
        l = m + 1;
      }
      else {
        r = m - 1;
      }
    }

    result.digits_[i] = x;
    current = current - b * x;
  }

  result.is_negative_ = lhs.is_negative_ != rhs.is_negative_;
  result.RemoveLeadingZeros();
  return result;
}

BigInteger& BigInteger::operator/=(const BigInteger& num) {
  return *this = (*this / num);
}

bool BigInteger::Odd() const {
  if (this->digits_.empty()) {
    return false;
  }
  return static_cast<bool>(this->digits_[0] & 1);
}

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
  Matrix(int height, int width) : height(height), width(width) {
    for (int i = 0; i < height; ++i) {
      matrix.emplace_back();
      for (int j = 0; j < width; ++j) {
        matrix[i].push_back(0);
      }
    }
  }
  Matrix(int dimension, MatrixType type) : height(dimension), width(dimension) {
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

  long long Sum() {
    long long sum = 0;
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        sum += matrix[i][j];
        sum %= modulo;
      }
    }
    return sum;
  }
};

Matrix global(1 << 7, ZERO);

void Multiply(Matrix& lhs, Matrix& rhs, Matrix& result) {
  for (int i = 0; i < lhs.height; ++i) {
    for (int j = 0; j < rhs.width; ++j) {
      global.matrix[i][j] = 0;
      for (int k = 0; k < lhs.width; ++k) {
        global.matrix[i][j] += (lhs.matrix[i][k] * rhs.matrix[k][j]);
        global.matrix[i][j] %= modulo;
      }
    }
  }
  for (int i = 0; i < lhs.height; ++i) {
    for (int j = 0; j < rhs.width; ++j) {
      result.matrix[i][j] = global.matrix[i][j];
    }
  }
}

void Pow(Matrix& matrix, BigInteger& deg, Matrix& result) {
  while (deg != 0) {
    if (deg.Odd()) {
      Multiply(result, matrix, result);
    }
    Multiply(matrix, matrix, matrix);
    deg /= 2;
  }
}

long long Pow(long long num, BigInteger& deg) {
  long long result = 1;
  while (deg != 0) {
    if (deg.Odd()) {
      result = (result * num) % modulo;
    }
    num = (num * num) % modulo;
    deg /= 2;
  }
  return result;
}

int main() {
  long long m;
  std::string s;
  std::cin >> s >> m >> modulo;
  BigInteger n(s);

  if (m == 1) {
    std::cout << Pow(2, n);
    return 0;
  }

  Matrix result(1 << m, UNIT);
  n -= 1;
  Matrix a(static_cast<int>(m), SPECIAL);
  Pow(a, n, result);

  std::cout << result.Sum();
}
// clan-format on