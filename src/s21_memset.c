#include "s21_string.h"

void *s21_memset(void *destptr, int c, s21_size_t num) {
  unsigned char *cdestptr = (unsigned char *)destptr;
  while (num--) *cdestptr++ = (unsigned char)c;
  return destptr;
}
