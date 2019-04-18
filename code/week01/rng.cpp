#include <iostream>

int rng(unsigned int previous) {
  return (100 * previous + 5) % 23;
}

int main() {
  unsigned int x = 5;
  for (int i = 0; i < 10; ++i) {
    x = rng(x);
    std::cout << x << "\n";
  }
  return 0;
}
