#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

int ReverseBits(int number, int bits_count) {
  int reverse_number = 0;
  while (bits_count >= 0 && number != 0) {
    if ((number & 1) != 0) {
      reverse_number |= (1 << bits_count);
    }
    number >>= 1;
    --bits_count;
  }
  return reverse_number;
}

void Permute(std::vector<std::complex<double>>& polynomial) {
  int bits_count = static_cast<int>(std::log2(polynomial.size())) - 1;
  std::vector<std::complex<double>> new_polynomial(polynomial.size());
  for (int i = 0; i < static_cast<int>(polynomial.size()); ++i) {
    new_polynomial[ReverseBits(i, bits_count)] = polynomial[i];
  }
  polynomial = new_polynomial;
}

void Transform(std::vector<std::complex<double>>& polynomial, int begin,
               int end, bool is_reverse) {
  int size = (end - begin) / 2;
  std::complex<double> omega(std::cos(M_PI / size), std::sin(M_PI / size));
  if (is_reverse) {
    omega = std::complex<double>(1) / omega;
  }
  std::complex<double> new_omega = 1;
  for (int i = begin; i < begin + size; ++i) {
    auto value1 = polynomial[i] + new_omega * polynomial[i + size];
    auto value2 = polynomial[i] - new_omega * polynomial[i + size];
    polynomial[i] = value1;
    polynomial[i + size] = value2;
    new_omega *= omega;
  }
}

void FFT(std::vector<std::complex<double>>& polynomial, bool is_reverse) {
  Permute(polynomial);
  for (int size = 2; size <= static_cast<int>(polynomial.size()); size *= 2) {
    for (int i = 0; i < static_cast<int>(polynomial.size()); i += size) {
      Transform(polynomial, i, i + size, is_reverse);
    }
  }
}

void Multiply(std::vector<int>& polynomial1, std::vector<int>& polynomial1)

int main() {
  int degree1;
  int degree2;
  std::cin >> degree1;
  std::vector<std::complex<double>> polynomial1(degree1 + 1);
  for (size_t i = 0; i < polynomial1.size(); ++i) {
    int coefficient;
    std::cin >> coefficient;
    polynomial1[degree1 - i] = coefficient;
  }
  std::cin >> degree2;
  std::vector<std::complex<double>> polynomial2(degree2 + 1);
  for (size_t i = 0; i < polynomial2.size(); ++i) {
    int coefficient;
    std::cin >> coefficient;
    polynomial2[degree2 - i] = coefficient;
  }

  int step = degree1 + degree2;
  step = static_cast<int>(pow(static_cast<double>(2), ceil(log2(step + 2))));

  for (size_t i = polynomial1.size(); i < static_cast<size_t>(step); ++i) {
    polynomial1.emplace_back(0);
  }
  for (size_t i = polynomial2.size(); i < static_cast<size_t>(step); ++i) {
    polynomial2.emplace_back(0);
  }

  std::complex<double> omega(std::cos(2 * M_PI / step),
                             std::sin(2 * M_PI / step));

  FFT(polynomial1, false);
  FFT(polynomial2, false);

  std::vector<std::complex<double>> result(step);
  for (int i = 0; i < step; ++i) {
    result[i] = polynomial1[i] * polynomial2[i];
  }

  FFT(result, true);

  int answer_size = degree2 + degree1;
  std::cout << answer_size << ' ';
  for (int i = answer_size; i >= 0; --i) {
    std::cout << static_cast<int>(
                     round(result[i].real() / static_cast<double>(step)))
              << ' ';
  }
}