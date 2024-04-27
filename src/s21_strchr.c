#include "s21_string.h"

/* Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
которую указывает аргумент str.
Возвращаемое значение:
Указатель на искомый символ, если он найден в строке str, иначе NULL.
*/
char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t n = s21_strlen(str);
  for (s21_size_t i = 0; i <= n; i++) {
    if (str[i] == c) {
      res = (char *)str + i;
      break;
    }
  }
  return res;
}

// int main() {
//   char str[] = "helopl";
//   printf("%ld\n", strchr(str, 'o') - str + 1);
//   printf("%ld\n", s21_strchr(str, 'o') - str + 1);
//   return 0;
// }
