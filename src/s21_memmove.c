#include "s21_string.h"

void *s21_memmove(void *destptr, const void *srcptr, s21_size_t num) {
  char *cdestptr = (char *)destptr;
  const char *csrcptr = (const char *)srcptr;
  char *tmp = (char *)malloc(sizeof(char) * num);
  if (tmp == s21_NULL) {
    return s21_NULL;
  } else {
    s21_size_t i = 0;
    for (i = 0; i < num; i++) *(tmp + i) = *(csrcptr + i);
    for (i = 0; i < num; i++) *(cdestptr + i) = *(tmp + i);
    free(tmp);
  }
  return destptr;
}
