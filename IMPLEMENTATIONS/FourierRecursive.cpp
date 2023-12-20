#include <complex>
#include <iostream>
#include <math.h>
#include <vector>

template <typename Complex_Vector = std::vector<std::complex<double>>>
Complex_Vector FFT(Complex_Vector polynomial, int k, std::complex<double> omega) {
  if (k == 1) {
    return {polynomial[0]};
  }
  Complex_Vector polynomial0;
  for (int i = 0; i < polynomial.size(); i += 2) {
    polynomial0.push_back(polynomial[i]);
  }
  Complex_Vector polynomial1;
  for (int i = 1; i < polynomial.size(); i += 2) {
    polynomial1.push_back(polynomial[i]);
  }

  auto new_omega = omega * omega;
  polynomial0 = FFT(polynomial0, k / 2, new_omega);
  polynomial1 = FFT(polynomial1, k / 2, new_omega);

  new_omega = 1;
  for (int i = 0; i < (k / 2); ++i) {
    polynomial[i] = polynomial0[i] + new_omega * polynomial1[i];
    polynomial[i + (k / 2)] = polynomial0[i] - new_omega * polynomial1[i];
    new_omega *= omega;
  }

  return polynomial;
}

int main() {
  std::vector<std::complex<double>> p{1, 2, 3, 4, 0, 0, 0, 0};
  std::vector<std::complex<double>> q{1, 2, 3, 4, 0, 0, 0, 0};

  int k = 8;
  std::complex<double> omega(std::cos(2 * M_PI / k), std::sin(2 * M_PI / k));

  p = FFT(p, k, omega);
  q = FFT(q, k, omega);

  std::vector<std::complex<double>> ans;
  for (int i = 0; i < k; ++i) {
    ans.push_back(p[i] * q[i]);
  }

  ans = FFT(ans, k, std::complex<double>(1) / omega);

  for (auto item : ans) {
    std::cout << item.real() / k << ' ';
  }
}