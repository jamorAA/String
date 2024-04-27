#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  int flag = 0;
  for (size_t i = 0; (str1[i] || str2[i]) && (i < n); i++) {
    if (str1[i] != str2[i]) {
      flag = str1[i] - str2[i];
      break;
    }
  }
  return flag;
}
