#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

template <typename T>
struct Vector {
 public:
  explicit Vector(size_t dimension) : begin(dimension), end(dimension) {}

  Vector operator+(const Vector& other);

  size_t Dimension() { return begin.size(); }
  long double Length();

  std::vector<T> begin;
  std::vector<T> end;
};

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) {
  Vector<T> result(this->Dimension());
  for (size_t i = 0; i < this->Dimension(); ++i) {
    result.begin[i] = 0;
    result.end[i] =
        this->end[i] - this->begin[i] + other.end[i] - other.begin[i];
  }
  return result;
}

template <typename T>
long double Vector<T>::Length() {
  long double length = 0;
  for (size_t i = 0; i < this->Dimension(); ++i) {
    auto difference = end[i] - begin[i];
    length += difference * difference;
  }
  return std::sqrt(length);
}

template <typename T>
T ScalarProduct(Vector<T>& lhs, Vector<T>& rhs) {
  T result = 0.0;
  for (size_t i = 0; i < lhs.Dimension(); ++i) {
    result += (lhs.end[i] - lhs.begin[i]) * (rhs.end[i] - rhs.begin[i]);
  }
  return result;
}

template <typename T>
long double Angle(Vector<T>& lhs, Vector<T>& rhs) {
  return std::acos(ScalarProduct(lhs, rhs) / (lhs.Length() * rhs.Length()));
}

template <typename T>
long double CrossProduct(Vector<T>& lhs, Vector<T>& rhs) {
  return lhs.Length() * rhs.Length() * sin(Angle(lhs, rhs));
}

template <typename T>
long double StupidCrossProduct(Vector<T>& lhs, Vector<T>& rhs) {
  return (lhs.end[0] - lhs.begin[0]) * (rhs.end[1] - rhs.begin[1]) -
         (rhs.end[0] - rhs.begin[0]) * (lhs.end[1] - lhs.begin[1]);
}

int main() {
  const size_t kDimension = 2;
  Vector<long double> vector1(kDimension);
  Vector<long double> vector2(kDimension);

  for (size_t i = 0; i < kDimension; ++i) {
    std::cin >> vector1.begin[i];
  }
  for (size_t i = 0; i < kDimension; ++i) {
    std::cin >> vector1.end[i];
  }
  for (size_t i = 0; i < kDimension; ++i) {
    std::cin >> vector2.begin[i];
  }
  for (size_t i = 0; i < kDimension; ++i) {
    std::cin >> vector2.end[i];
  }

  const int kPrecision = 7;
  std::cout << std::fixed;
  std::cout << std::setprecision(kPrecision);
  std::cout << vector1.Length() << ' ' << vector2.Length() << '\n';
  auto vector3 = vector1 + vector2;
  std::cout << vector3.end[0] << ' ' << vector3.end[1] << '\n';
  std::cout << ScalarProduct(vector1, vector2) << ' '
            << StupidCrossProduct(vector1, vector2) << '\n';
  std::cout << std::abs(CrossProduct(vector1, vector2) / 2);
}