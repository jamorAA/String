#include "s21_string.h"

char *s21_strcpy(char *destptr, const char *srcptr) {
  char *ptr = destptr;
  while (*srcptr != '\0') *(destptr++) = *(srcptr++);
  *destptr = '\0';
  return ptr;
}
