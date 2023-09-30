#include <algorithm>
#include <iostream>

long long a0, k, n, x, y;
long long cnt = 0, cnt1 = 0, cnt2 = 0, m_cnt = 0;
long long t = (1 << 30);

void Initialize(long long* arr, long long& cur_idx) {
  while (cur_idx < k) {
    a0 = (x * a0 + y) % t;
    cnt++;
    arr[cur_idx++] = a0;
    if (cnt == n) {
      break;
    }
  }
}

void MergeExt(long long* a1, const long long* a2, long long* m_a) {
  int count = 0;
  int i = 0, j = 0;
  while (m_cnt != k) {
    if (j == cnt2 || a1[i] < a2[j]) {
      m_a[m_cnt] = a1[i];
      a1[count] = m_a[count];
      count++;
      i++;
    } else {
      m_a[m_cnt] = a2[j];
      j++;
    }
    m_cnt++;
  }
  while (count < k) {
    a1[count] = m_a[count];
    count++;
  }
}

int main() {
  std::cin >> n >> k;
  std::cin >> a0 >> x >> y;
  long long* a1 = new long long[k + 1];
  long long* a2 = new long long[k + 1];
  long long* m_a = new long long[k + 1];
  Initialize(a1, cnt1);
  std::sort(a1, a1 + k);
  while (cnt < n) {
    Initialize(a2, cnt2);
    std::sort(a2, a2 + cnt2);
    MergeExt(a1, a2, m_a);
    cnt2 = 0;
    m_cnt = 0;
  }
  for (int i = 0; i < k; ++i) {
    std::cout << a1[i] << ' ';
  }
  delete[] a1;
  delete[] a2;
  delete[] m_a;
  return 0;
}