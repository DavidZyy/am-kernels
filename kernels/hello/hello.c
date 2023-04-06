#include <am.h>
#include <klib-macros.h>

#include <klib.h>

int main(const char *args) {
  const char *fmt =
    "Hello, AbstractMachine!\n"
    "mainargs = '%'.\n";

  for (const char *p = fmt; *p; p++) {
    (*p == '%') ? putstr(args) : putch(*p);
  }

  printf("i have 1234 pencils.\n");

  // printf("i have %d pencils.\n", 1234);

  // char buffer[256];
  // sprintf(buffer, "i have %d pencils.\n", 1234);
  // for(int i = 0; buffer[i] != '\0'; i++)
  //   putch(buffer[i]);

  return 0;
}
