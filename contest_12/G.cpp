#include <algorithm>
#include <iostream>
#include <vector>

#define lll long long

#define pw(nn) (1 << nn)
const lll kN = 100000;
const lll kMod = 7340033;
const lll kGG = 3;
lll nn;
lll mm;
lll bit;
lll bitnum;
lll aa[kN + 5];
lll bb[kN + 5];
lll rev[kN + 5];

void Getrev(lll ll) {
  for (lll i = 0; i < pw(ll); i++) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << std::abs(ll - 1));
  }
}

lll Fastpow(lll aaa, lll bbb) {
  lll ans = 1;
  for (; bool(bbb); bbb >>= 1, aaa = 1LL * aaa * aaa % kMod) {
    if (bool(bbb & 1)) {
      ans = 1LL * ans * aaa % kMod;
    }
  }
  return ans;
}

void NTT(lll* ss, lll op) {
  for (lll i = 0; i < bit; i++) {
    if (i < rev[i]) {
      std::swap(ss[i], ss[rev[i]]);
    }
  }
  for (lll i = 1; i < bit; i <<= 1) {
    lll ww = Fastpow(kGG, (kMod - 1) / (i << 1));
    for (lll pp = i << 1, j = 0; j < bit; j += pp) {
      lll wk = 1;
      for (lll k = j; k < i + j; k++, wk = 1LL * wk * ww % kMod) {
        lll xx = ss[k];
        lll yy = 1LL * ss[k + i] * wk % kMod;
        ss[k] = (xx + yy) % kMod;
        ss[k + i] = (xx - yy + kMod) % kMod;
      }
    }
  }
  if (op == -1) {
    std::reverse(ss + 1, ss + bit);
    lll inv = Fastpow(bit, kMod - 2);
    for (lll i = 0; i < bit; i++) {
      aa[i] = 1LL * aa[i] * inv % kMod;
    }
  }
}

void Solve(std::vector<lll> pol_a, std::vector<lll> pol_b,
           std::vector<lll>& cc) {
  nn = static_cast<long long>(pol_a.size() - 1);
  mm = static_cast<long long>(pol_b.size() - 1);
  for (lll i = 0; i <= nn; i++) {
    aa[i] = pol_a[i];
  }
  for (lll i = 0; i <= mm; i++) {
    bb[i] = pol_b[i];
  }
  mm += nn;
  bitnum = 0;
  for (bit = 1; bit <= mm; bit <<= 1) {
    bitnum++;
  }
  Getrev(bitnum);
  NTT(aa, 1);
  NTT(bb, 1);
  for (lll i = 0; i < bit; i++) {
    aa[i] = 1LL * aa[i] * bb[i] % kMod;
  }
  NTT(aa, -1);
  cc.clear();
  for (lll i = 0; i <= mm; i++) {
    cc.push_back(aa[i]);
  }
  for (lll i = 0; i <= std::min(mm * 2, kN - 1); i++) {
    aa[i] = bb[i] = 0;
  }
}

struct Poly {
  std::vector<lll> aa;

  void Cut(lll nnn) {
    while (static_cast<long long>(aa.size()) > nnn) {
      aa.pop_back();
    }
  }

  Poly operator*(lll bbb) {
    Poly ccc = *this;
    for (lll i = 0; i < static_cast<long long>(aa.size()); i++) {
      (((ccc.aa[i] *= bbb) %= kMod) += kMod) %= kMod;
    }
    return ccc;
  }

  Poly operator*(const Poly& bbb) const {
    Poly ccc;
    Solve(aa, bbb.aa, ccc.aa);
    return ccc;
  }

  Poly operator+(Poly bbb) {
    lll len = static_cast<long long>(std::max(aa.size(), bbb.aa.size()));
    aa.resize(len);
    bbb.aa.resize(len);
    Poly ccc;
    for (lll i = 0; i < len; i++) {
      ccc.aa.push_back((aa[i] + bbb.aa[i]) % kMod);
    }
    return ccc;
  }

  Poly operator-(Poly bbb) {
    lll len = static_cast<long long>(std::max(aa.size(), bbb.aa.size()));
    aa.resize(len);
    bbb.aa.resize(len);
    Poly ccc;
    for (lll i = 0; i < len; i++) {
      ccc.aa.push_back(((aa[i] - bbb.aa[i]) % kMod + kMod) % kMod);
    }
    return ccc;
  }
};

void Print(const Poly& xx) {
  for (long long item : xx.aa) {
    std::cout << item << " ";
  }
}

lll Qpow(lll pp, lll qq) {
  lll rr = 1;
  for (; bool(qq); pp *= pp, pp %= kMod, qq >>= 1) {
    if (bool(qq & 1)) {
      rr *= pp, rr %= kMod;
    }
  }
  return rr;
}

lll Inv(lll pp) { return Qpow(pp, kMod - 2); }

Poly Solve(Poly pol_a, lll nnn) {
  pol_a.Cut(nnn);
  Poly pol_b;
  if (nnn == 1) {
    pol_b.aa.push_back(Inv(pol_a.aa[0]));
  } else {
    Poly bi = Solve(pol_a, (nnn - 1) / 2 + 1);
    pol_b = bi * 2 - pol_a * bi * bi;
    pol_b.Cut(nnn);
  }
  return pol_b;
}

signed main() {
  std::ios::sync_with_stdio(false);
  lll mmm;
  std::cin >> mmm >> nn;
  nn += 1;
  for (lll i = 0; i < nn; i++) {
    std::cin >> aa[i];
  }
  Poly pol_a;
  for (lll i = 0; i < nn; i++) {
    pol_a.aa.push_back(aa[i]);
  }
  Poly pol_b = Solve(pol_a, nn);

  bool flag = true;
  for (lll i = 0;
       i < static_cast<long long>(std::min(pol_a.aa.size(), pol_b.aa.size()));
       ++i) {
    if (pol_a.aa[i] != pol_b.aa[i]) {
      flag = false;
    }
  }
  if (flag) {
    std::cout << "The ears of a dead donkey";
    return 0;
  }

  Print(pol_b);
  for (lll i = static_cast<lll>(pol_b.aa.size()); i < mmm; ++i) {
    std::cout << 0 << ' ';
  }
}