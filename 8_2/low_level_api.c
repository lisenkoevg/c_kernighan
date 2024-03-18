#include <unistd.h>

#define BUF_SIZE 100

int main() {
  char buf[10];
  int n;
  while ((n = read(0, buf, BUF_SIZE)) > 0)
    write(1, buf, n);
  return 0;
}
