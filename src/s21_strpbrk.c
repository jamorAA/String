#include "s21_string.h"
/* Находит первый символ в строке str1, который соответствует любому символу,
указанному в str2.
Возвращаемое значение:
NULL – если не один символ из cтроки str2 не найден в строке str1.
Указатель на первый найденный в строке str символ из множества символов строки
str2.
*/
char *s21_strpbrk(const char *base_str, const char *search_str) {
  char *res = s21_NULL;
  int flag = 0;

  for (int i = 0; base_str[i] != '\0'; i++) {
    for (int j = 0; search_str[j] != '\0'; j++) {
      if (base_str[i] == search_str[j]) {
        res = (char *)base_str + i;
        flag = 1;
        break;
      }
    }
    if (flag) {
      break;
    }
  }
  return res;
}

// int main() {
//   char str1[] = "helopl";
//   char str2[] = "plh";
//   printf("%ld\n", strpbrk(str1, str2) - str1 + 1);
//   printf("%ld\n", s21_strpbrk(str1, str2) - str1 + 1);
//   return 0;
// }
