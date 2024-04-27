#include "s21_string.h"

int s21_memcmp(const void *string1, const void *string2, s21_size_t lenght) {
  int cmp = 0;
  if (string1 != s21_NULL && string2 != s21_NULL) {
    for (s21_size_t i = 0; i < lenght; i++) {
      if (*(char *)string1 != *(char *)string2 && !cmp) {
        cmp = ((*(char *)string1) - (*(char *)string2));
      }
      string1++;
      string2++;
    }
  }
  return cmp;
}