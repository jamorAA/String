#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, size_t n) {
  int len = 0;
  for (int i = 0; dest[i] != '\0'; i++) {
    len++;
  }

  for (s21_size_t i = 0; i < n && *src != '\0'; i++) {
    dest[len + i] = src[i];
  }
  return dest;
}
