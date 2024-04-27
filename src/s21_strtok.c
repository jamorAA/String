#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = {0};
  if (str) last = str;
  if ((last == s21_NULL) || (*last == 0)) return s21_NULL;
  char *c = last;
  while (s21_strchr(delim, *c)) ++c;
  if (*c == 0) return 0;
  char *start = c;
  while (*c && (s21_strchr(delim, *c) == 0)) ++c;
  if (*c == 0) {
    last = c;
    return start;
  }
  *c = 0;
  last = c + 1;
  return start;
}

// int main(){
// char dest[] = " s\0";
// char orig[] = " s\0";
// printf("%p\n", s21_strtok(dest ,"s"));
// printf("%p\n", strtok(orig,"s"));
// }
