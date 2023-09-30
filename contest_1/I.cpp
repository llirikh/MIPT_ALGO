#include <algorithm>
#include <iostream>

using namespace std;

int n, k;
int a[100'000];

bool AnsCheck(int l, int k1) {
  int f = a[0] + l;
  k1--;
  for (int i = 0; i < n; i++) {
    if (f < a[i]) {
      k1--;
      f = a[i] + l;
      if (k1 < 0) {
        return false;
      }
    }
  }
  return true;
}

int BinSearch() {
  int l = 0;
  int r = a[n - 1] - a[0];
  while (r != l) {
    int m = l + (r - l) / 2;
    if (m == r || m == l) {
      return r;
    }
    if (AnsCheck(m, k)) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

int main() {
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a + n);
  int cnt = 1;
  for (int i = 1; i < n; i++) {
    if (a[i] != a[i - 1]) {
      cnt++;
    }
  }
  if (k >= cnt) {
    cout << 0;
  } else {
    cout << BinSearch();
  }
  return 0;
}