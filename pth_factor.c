#include <stdio.h>

long pthFactor(long n, long p);

int main() {
    printf("%ld\n",pthFactor(10, 3));
    return 0;
}

long pthFactor(long n, long p) {
  long factorCount = 0;
  for (long i = 1; i <= n; i++) {
    if (n % i == 0) {
      factorCount++;
      if (factorCount == p) {
        return i;
      }
    }
  }
  return 0;
}