#include "s21_string.h"

// int main() {
//   char str[] = {'q', 'r', 's', 't', 'w', 's', 'a', 's', 'b', '\0'};
//   char keys[] = "br";
//   // поиск первого вхождения в строку str любого из символов строки keys
//   int a2 = strcspn(str, keys);
//   int a1 = s21_strcspn(str, keys);
//   printf("%d\t%d\n", a1, a2);
//   return 0;
// }

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t ret = -1;
  int i = 0;
  int flag = 1;
  while (flag != 0 && ret != s21_strlen(str1)) {
    ret++;
    while (str2[i] != '\0') {
      if (str2[i] == str1[ret]) {
        flag = 0;
      }
      i++;
    }
    i = 0;
  }

  return ret;
}
