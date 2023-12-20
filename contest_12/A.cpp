#include <iostream>

static const long long kP = 1e9 + 7;

long long Mod(long long num, long long mod = kP) {
  if (num < 0) {
    return (num % mod + mod) % mod;
  }
  return num % mod;
}

long long Factor(long long num, long long deg) {
  if (deg == 0) {
    return 1;
  }
  if (deg % 2 == 0) {
    long long tmp = Mod(Factor(num, deg / 2));
    return Mod(tmp * tmp);
  }
  return Mod(num * Factor(num, deg - 1));
}

int main() {
  long long aa;
  long long bb;
  long long cc;
  long long dd;
  std::cin >> aa >> bb >> cc >> dd;
  long long num1 = Mod(aa * dd);
  long long num2 = Mod(bb * cc);
  long long num3 = Mod(Factor(Mod(bb * dd), kP - 2));
  std::cout << Mod(Mod(num1 + num2) * num3);
}