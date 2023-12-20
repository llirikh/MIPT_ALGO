#include <iostream>
#include <tuple>

long long PowerModulo(long long aa, long long bb, long long nn) {
  long long result = 1;
  while (bb != 0) {
    if (bb % 2 == 1) {
      result = (result * aa) % nn;
    }
    aa = (aa * aa) % nn;
    bb >>= 1;
  }
  return result;
}

std::tuple<long long, long long, long long> ExtendedGcd(long long aa,
                                                        long long bb) {
  if (aa == 0) {
    return std::make_tuple(bb, 0, 1);
  }

  if (bb == 0) {
    return std::make_tuple(aa, 1, 0);
  }

  long long un_prev = 1;
  long long vn_prev = 0;
  long long un_cur = 0;
  long long vn_cur = 1;

  while (true) {
    long long qn = aa / bb;
    long long new_r = aa % bb;
    aa = bb;
    bb = new_r;

    if (bb == 0) {
      return std::make_tuple(aa, un_cur, vn_cur);
    }

    long long un_new = un_prev - qn * un_cur;
    long long vn_new = vn_prev - qn * vn_cur;

    un_prev = un_cur;
    vn_prev = vn_cur;
    un_cur = un_new;
    vn_cur = vn_new;
  }
}

long long InverseModulo(long long aa, long long nn) {
  auto result = ExtendedGcd(aa, nn);
  return std::get<1>(result) % nn;
}

long long LegendreSymbol(long long aa, long long pp) {
  return PowerModulo(aa, (pp - 1) >> 1, pp);
}

long long ChooseB(long long pp) {
  long long bb = 2;
  while (LegendreSymbol(bb, pp) == 1) {
    bb = rand() % (pp - 2) + 2;
  }
  return bb;
}

long long TonelliShanksRecursive(long long aa, long long kk, long long pp,
                                 long long bb, long long b_inverse) {
  long long mm = (pp - 1) >> kk;
  long long a_m = 1;

  while (mm % 2 == 0 && a_m == 1) {
    mm >>= 1;
    kk += 1;
    a_m = PowerModulo(aa, mm, pp);
  }

  if (a_m == pp - 1) {
    long long b_power = 1 << (kk - 1);
    long long b_power_half = 1 << (kk - 2);
    long long a_next = (aa * PowerModulo(bb, b_power, pp)) % pp;
    long long a_next_root =
        TonelliShanksRecursive(a_next, kk, pp, bb, b_inverse);
    long long a_root =
        (a_next_root * PowerModulo(b_inverse, b_power_half, pp)) % pp;
    return a_root;
  }

  return PowerModulo(aa, (mm + 1) >> 1, pp);
}

long long TonelliShanks(long long aa, long long pp) {
  if (LegendreSymbol(aa, pp) != 1) {
    return -1;
  }

  long long bb = ChooseB(pp);
  long long b_inverse = InverseModulo(bb, pp);
  return TonelliShanksRecursive(aa, 1, pp, bb, b_inverse);
}

void Solve() {
  long long aa;
  long long pp;
  std::cin >> aa >> pp;

  if (pp == 2 || aa == 0) {
    std::cout << aa << '\n';
    return;
  }

  long long result = TonelliShanks(aa, pp);

  if (result == -1) {
    std::cout << "IMPOSSIBLE";
  } else {
    std::cout << (result < 0 ? -result : result);
  }
  std::cout << '\n';
}

int main() {
  srand(time(0));

  long long num;
  std::cin >> num;

  while (num-- != 0) {
    Solve();
  }

  return 0;
}
