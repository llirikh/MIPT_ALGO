#include <cmath>
#include <complex>
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