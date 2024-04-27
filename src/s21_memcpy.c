#include "s21_string.h"

void *s21_memcpy(void *destptr, const void *srcptr, s21_size_t num) {
  char *cdestptr = (char *)destptr;
  const char *csrcptr = (const char *)srcptr;
  if ((cdestptr != s21_NULL) && (csrcptr != s21_NULL)) {
    while (num) {
      *(cdestptr++) = *(csrcptr++);
      --num;
    }
  }
  return destptr;
}
