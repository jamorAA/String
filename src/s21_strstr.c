#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  s21_size_t i, j, k;
  if (s21_strlen(needle) == 0) {
    res = (char *)haystack;
  }
  for (i = 0; haystack[i] != '\0'; i++) {
    for (j = i, k = 0; needle[k] != '\0' && haystack[j] == needle[k]; j++, k++)
      ;

    if (k > 0 && needle[k] == '\0') {
      res = (char *)haystack + i;
      break;
    }
  }
  return res;
}

// int main() {
//   char *str1 = "heloplfgflop";
//   char *str2 = "lopl";
//   char *out1 = strstr(str1, str2);
//   char *out2 = s21_strstr(str1, str2);
//   if (out2 == NULL) {
//     puts("Строка не найдена");
//     printf("%p\n", out2);
//   } else {
//     printf("%p %s %ld\n", out1, out1, out1 - str1 + 1);
//     printf("%p %s %ld\n", out2, out2, out2 - str1 + 1);
//   }
//   return 0;
// }