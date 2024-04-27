#include "s21_string.h"

char *s21_strncpy(char *destptr, const char *srcptr, s21_size_t num) {
  size_t i;
  for (i = 0; i < num && srcptr[i] != '\0'; i++) destptr[i] = srcptr[i];
  for (; i < num; i++) destptr[i] = '\0';
  return destptr;
}
