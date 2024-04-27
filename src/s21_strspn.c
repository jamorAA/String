#include "s21_string.h"
/*
int main() {
  char strtext[] = "12-йгод123";                // строка, в которой выполняется
поиск char digit[] = "1234567890";               // строка искомых символов int
num1 = s21_strspn(strtext, digit); int num2 = strspn(strtext, digit);
  printf("%d\t%d\n", num1, num2);
  return 0;
}*/

/* s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t ret = -1;
  int i = 0;
  int true = 1;
  while (true) {
    ret++;
    true = 0;
    while (str2[i] != '0') {
      if (str2[i] == str1[ret]) {
        true = 1;
      }
      i++;
    }
    i = 0;
  }
  return ret;
} */

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  while (str1[i]) {
    if (!s21_strchr(str2, str1[i])) {
      break;
    }
    i++;
  }
  return i;
}