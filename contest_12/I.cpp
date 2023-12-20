#include <iostream>
#include <vector>
using namespace std;

// Функция для добавления многочленов по модулю 7
vector<int> addPolynomials(const vector<int>& a, const vector<int>& b) {
  size_t degree = max(a.size(), b.size());
  vector<int> result(degree, 0);
  for (size_t i = 0; i < degree; ++i) {
    int aValue = i < a.size() ? a[i] : 0;
    int bValue = i < b.size() ? b[i] : 0;
    result[i] = (aValue + bValue) % 7;
  }
  return result;
}

// Функция для умножения многочлена на моном (x^n) по модулю 7
vector<int> multiplyByXn(const vector<int>& a, int n) {
  vector<int> result(a.size() + n, 0);
  for (size_t i = 0; i < a.size(); ++i) {
    result[i + n] = a[i];
  }
  return result;
}

// Функция для умножения многочлена на константу по модулю 7
vector<int> multiplyByConstant(const vector<int>& a, int constant) {
  vector<int> result(a.size(), 0);
  for (size_t i = 0; i < a.size(); ++i) {
    result[i] = (a[i] * constant) % 7;
  }
  return result;
}

// Функция для нахождения обратного элемента по умножению в поле Z/7
int modInverse(int a) {
  for (int x = 1; x < 7; x++) {
    if ((a * x) % 7 == 1) return x;
  }
  return 1; // Никогда не должно произойти, так как a != 0 и мы в поле Z/7
}

// Функция для деления многочленов по модулю 7
pair<vector<int>, vector<int>> dividePolynomials(const vector<int>& dividend, const vector<int>& divisor) {
  vector<int> quotient;
  vector<int> remainder = dividend;

  while (remainder.size() >= divisor.size()) {
    int coef = modInverse(divisor.back()) * remainder.back() % 7;
    int degreeDiff = remainder.size() - divisor.size();
    vector<int> term = multiplyByXn(multiplyByConstant(divisor, coef), degreeDiff);

    quotient.push_back(coef);
    remainder = addPolynomials(remainder, multiplyByConstant(term, 6)); // Вычитаем term по модулю 7

    // Удаляем нулевые старшие коэффициенты
    while (!remainder.empty() && remainder.back() == 0) {
      remainder.pop_back();
    }
  }

  reverse(quotient.begin(), quotient.end()); // Так как добавляли коэффициенты в начало

  return make_pair(quotient, remainder);
}

// Функция для вывода многочлена
void printPolynomial(const vector<int>& polynomial) {
  if (polynomial.empty()) {
    cout << "0 0" << endl;
  } else {
    cout << polynomial.size() - 1;
    for (auto it = polynomial.rbegin(); it != polynomial.rend(); ++it) {
      cout << " " << *it;
    }
    cout << endl;
  }
}

int main() {
  int k1, k2, coef;
  cin >> k1;
  vector<int> dividend(k1 + 1);
  for (int &c : dividend) cin >> c;

  cin >> k2;
  vector<int> divisor(k2 + 1);
  for (int &c : divisor) cin >> c;

  auto [quotient, remainder] = dividePolynomials(dividend, divisor);

  printPolynomial(quotient);
  printPolynomial(remainder);

  return 0;
}