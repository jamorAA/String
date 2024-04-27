#include "s21_string.h"

/* Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
которую указывает аргумент str.
Возвращаемое значение:
Указатель на искомый символ, если он найден в строке str, иначе NULL.
*/
char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t n = s21_strlen(str);
  for (int i = n; i >= 0; i--) {
    if (str[i] == c) {
      res = (char *)str + i;
      break;
    }
  }
  return res;
}

// int main() {
//   char *str = "helopl";
//   printf("%ld\n", strrchr(str, 'l') - str + 1);
//   printf("%ld\n", s21_strrchr(str, 'l') - str + 1);
//   return 0;
// }
