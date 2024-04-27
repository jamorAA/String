#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int lenght = 0;
  for (int i = 0; dest[i] != '\0'; i++) {
    lenght++;
  }
  for (int i = 0; src[i] != '\0'; i++) {
    dest[lenght + i] = src[i];
    dest[lenght + 1 + i] = '\0';
  }
  return dest;
}
