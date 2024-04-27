#include "s21_string.h"

char* s21_strerror(int errnum) {
  char* ERRORS[] = ERR_LIST;
  char* error = s21_NULL;
  char* fail = {0};
  static char buf[50];
  if (errnum >= 0 && errnum < N_ERR) {
    error = ERRORS[errnum];
  } else {
    if (std == 1) {
      fail = "Unknown error: ";
      s21_sprintf(buf, "%s%d", fail, errnum);
    } else if (std == 0) {
      fail = "Unknown error ";
      s21_sprintf(buf, "%s%d", fail, errnum);
    }
  }
  return error == s21_NULL ? buf : error;
}
