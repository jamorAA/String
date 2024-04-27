#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = NULL;

  if (src) {
    if (trim_chars && *trim_chars) {
      size_t length = s21_strlen(src);
      size_t chars_length = s21_strlen(trim_chars);

      s21_trim_left(&src, trim_chars, &length, chars_length);
      if (length) s21_trim_right(&src, trim_chars, &length, chars_length);

      result = (char *)malloc(sizeof(char) * (length + 1));

      if (result) {
        for (size_t i = 0; i < length + 1; i++) {
          if (i < length) {
            result[i] = src[i];
          } else {
            result[i] = '\0';
          }
        }
      }
    } else {
      result = s21_trim(src, " \t\n");
    }
  }

  return result;
}

void s21_trim_left(const char **src, const char *trim_chars, size_t *src_length,
                   const size_t trim_chars_length) {
  size_t n = 0;
  while (src && n != trim_chars_length) {
    if ((**src) == trim_chars[n]) {
      (*src)++;
      (*src_length) -= 1;
      n = 0;
      continue;
    }
    n++;
  }
}

void s21_trim_right(const char **src, const char *trim_chars,
                    size_t *src_length, const size_t trim_chars_length) {
  size_t n = 0;
  size_t i = (*src_length) - 1;
  while (src && n != trim_chars_length) {
    if ((*src)[i] == trim_chars[n]) {
      i--;
      (*src_length)--;
      n = 0;
      continue;
    }
    n++;
  }
}
