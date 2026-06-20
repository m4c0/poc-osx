#include <mach-o/ldsyms.h>
#include <mach-o/getsect.h>
#include <stdio.h>

int main() {
  unsigned long size = 0;
  char * data = (char *)getsectiondata(&_mh_execute_header, "myseg", "mysect", &size);
  printf("%.*s\n", (int)size, data);
  return 0;
}
