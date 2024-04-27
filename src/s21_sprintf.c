#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  va_list argList;
  va_start(argList, format);
  s21_size_t i = 0, flag = 0, error = 0;
  char *str_start = str;
  str = s21_strcpy(str, "");
  while (*format && error == 0) {
    format_sprintf Format = {0};
    Format.width = Format.tolerance = -1;
    Format.flag_error = Format.sharp = Format.zero = Format.minus =
        Format.space = Format.plus = 0;
    if (*format == '%') {
      flag = 1;
      format++;
    } else {
      str[i++] = *(format++);
      str[i] = '\0';
    }

    if (flag && is_flag(*format))
      while (is_flag(*format)) setflag(&Format, format++);

    if (flag && (is_digit(*format) || *format == '*'))
      format = str2int(format, &Format.width, &argList);

    if (flag && *format == '.') {
      Format.tolerance = 0;
      format = str2int(++format, &Format.tolerance, &argList);
    }

    if (flag && is_len(*format)) Format.len = *(format++);

    if (flag && is_spec(*format)) Format.spec = *(format++);

    if (flag) {
      str = format_param2str(str, &i, &Format, &argList);
      error = Format.flag_error;
    }
    flag = 0;
  }
  va_end(argList);
  if (error != 0) *str_start = '\0';
  return error == 0 ? (int)s21_strlen(str) : -1;
}

void setflag(format_sprintf *Format, const char *format) {
  switch (*format) {
    case '-':
      Format->minus = 1;
      break;
    case '+':
      Format->plus = 1;
      break;
    case ' ':
      Format->space = 1;
      break;
    case '#':
      Format->sharp = 1;
      break;
    case '0':
      Format->zero = 1;
      break;
  }
}

char *format_param2str(char *str, s21_size_t *str_len, format_sprintf *Format,
                       va_list *argList) {
  char *temp_str = s21_NULL;
  temp_str = calloc(1000 + Format->width + 2, sizeof(char));
  if (temp_str != s21_NULL) {
    switch (Format->spec) {
      case 'd':
      case 'i':
        specd(temp_str, argList, Format);
        break;
      case 'o':
        speco(temp_str, argList, Format);
        break;
      case 'u':
        specu(temp_str, argList, Format);
        break;
      case 'x':
      case 'X':
        specxX(temp_str, argList, Format);
        break;
      case 'e':
      case 'E':
        speceE(temp_str, argList, Format);
        break;
      case 'f':
        specf(temp_str, argList, Format);
        break;
      case 'g':
      case 'G':
        specgG(temp_str, argList, Format);
        break;
      case 'c':
        specC(temp_str, argList, Format);
        break;
      case 's':
        specS(temp_str, argList, Format);
        break;
      case 'p':
        specp(temp_str, argList, Format);
        break;
      case 'n':
        specn(str_len, argList);
        break;
      case '%':
        specPrec(temp_str, Format);
        break;
    }
    s21_strcat(str, temp_str);
    free(temp_str);
    *str_len = s21_strlen(str);
  }
  return str;
}

void specn(s21_size_t const *str_len, va_list *argList) {
  int *p = va_arg(*argList, int *);
  *p = (int)*str_len;
}

char *specPrec(char *str, format_sprintf *Format) {
  Format->tolerance = 0;
  s21_strcat(str, "%");
  ll_tolerance(str, Format);
  ll_width_flag(str, Format);
  return str;
}

char *specp(char *str, va_list *argList, format_sprintf *Format) {
  int width = Format->width < 15 ? 15 : Format->width;
  char *str_start = s21_NULL;
  str_start = str;
  int *p = va_arg(*argList, int *);
  char buf[4] = "x0";
  if (p == s21_NULL) {
    s21_strcpy(buf, "0x0");
  }

  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((s21_size_t)j) >> 4), k++) {
    unsigned int dig = ((s21_size_t)j) % 0x10;
    if (dig < 10 && Format->spec == 'p')
      *(str_start++) = (char)('0' + dig);
    else
      *(str_start++) = (char)('a' + (dig - 10));
  }
  *str_start = '\0';
  s21_strcat(str, buf);
  reverse_str(str);
  ll_width_flag(str, Format);
  return str;
}

char *specf(char *str, va_list *argList, format_sprintf *Format) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (Format->len) {
    case 'l':
      d_number = (double)va_arg(*argList, double);
      lf2str(str, d_number, Format);
      break;
    case 'L':
      ld_number = va_arg(*argList, long double);
      lf2str(str, ld_number, Format);
      break;
    default:
      d_number = va_arg(*argList, double);
      f_number = d_number;
      lf2str(str, f_number, Format);
  }
  signflag(str, Format);
  lf_width_flag(str, Format);
  return str;
}

char *speceE(char *str, va_list *argList, format_sprintf *Format) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (Format->len) {
    case 'l':
      d_number = (double)va_arg(*argList, double);
      leE2str(str, d_number, Format);
      break;
    case 'L':
      ld_number = va_arg(*argList, long double);
      leE2str(str, ld_number, Format);
      break;
    default:
      d_number = va_arg(*argList, double);
      f_number = d_number;
      leE2str(str, f_number, Format);
  }
  signflag(str, Format);
  lf_width_flag(str, Format);
  return str;
}

char *specgG(char *str, va_list *argList, format_sprintf *Format) {
  long double ld_number;
  double d_number;
  double f_number;

  switch (Format->len) {
    case 'l':
      d_number = (double)va_arg(*argList, double);
      lgG2str(str, d_number, Format);
      break;
    case 'L':
      ld_number = va_arg(*argList, long double);
      lgG2str(str, ld_number, Format);
      break;
    default:
      d_number = va_arg(*argList, double);
      f_number = d_number;
      lgG2str(str, f_number, Format);
  }
  signflag(str, Format);
  lf_width_flag(str, Format);
  return str;
}

char *leE2str(char *str, long double number, format_sprintf *Format) {
  if (Format->tolerance < 0) Format->tolerance = 6;
  long double right = 0.0, mantis;
  int pow = 0;

  mantis = modfl(fabsl(number), &right);
  if (fpclassify(number) > 3) {
    while (right >= 10) {
      pow++;
      modfl(right / 10, &right);
    }
    if (pow == 0 && right < 1) {
      while (truncl(mantis * powl(10, pow * -1)) < 1) {
        pow--;
      }
    }
  }

  if (fpclassify(number) > 2) {
    number = number / powl(10, pow);
    s21_sprintf(str, Format->sharp ? "%#.*Lfe%+.2d" : "%.*Lfe%+.2d",
                Format->tolerance, number, pow);
  } else {
    s21_sprintf(str, "%.*Lf", Format->tolerance);
    Format->zero = 0;
  }
  if (Format->spec == 'E') {
    char *p = s21_NULL;
    p = s21_strchr(str, 'e');
    if (p) *p = 'E';
  }
  return str;
}

char *lgG2str(char *str, long double number, format_sprintf *Format) {
  if (Format->tolerance < 0) Format->tolerance = 6;
  long double right = 0.0;
  int pow = 0, pow_m = 0;

  long double mantis = modfl(fabsl(number), &right);
  if (fpclassify(mantis) > 3 && fpclassify(right) == 3) {
    while (truncl(mantis * powl(10, pow * -1)) < 1) {
      pow--;
    }
  }
  mantis = modfl(fabsl(number), &right);
  if (fpclassify(number) > 3) {
    while (right >= 1 && pow >= 0) {
      pow++;
      modfl(right / 10, &right);
    }
    if (fpclassify(mantis) > 3) {
      for (int i = 0; i < Format->tolerance - pow; i++) {
        mantis = modfl(right / 10, &right);
        if (fpclassify(mantis) > 3) {
          pow_m++;
        }
      }
    }
  }

  int flag;
  int tolerance;
  if (pow - 1 < -4 || pow - 1 > Format->tolerance - 1) {
    flag = 1;
    tolerance = Format->tolerance > 0 ? Format->tolerance - 1 : 0;
  } else {
    flag = 0;
    if (pow < 0)
      tolerance = Format->tolerance > 0 ? Format->tolerance : 0;
    else
      tolerance = Format->tolerance > 0 ? Format->tolerance - pow : 0;
  }

  if (flag) {
    if (Format->spec == 'G')
      s21_sprintf(str, Format->sharp ? "%#.*LE" : "%.*LE", tolerance, number);
    else
      s21_sprintf(str, Format->sharp ? "%#.*Le" : "%.*Le", tolerance, number);
  } else {
    s21_sprintf(str, Format->sharp ? "%#.*Lf" : "%.*Lf", tolerance, number);
  }

  char *p = s21_NULL;
  if (pow < 0 && flag) {
    p = str;
    s21_size_t str_len = s21_strpbrk(str, Format->spec == 'G' ? "E" : "e") - p;
    if (str_len > 2 && (int)str_len - 1 >= Format->tolerance &&
        *(p + str_len - 1) == '0' && Format->sharp == 0) {
      p = p + str_len - 1;
      while (*p == '0') {
        *(p--) = '\0';
      }
      p = str + str_len;
      s21_strcat(str, p);
    }
  }

  p = str;
  p = p + s21_strlen(str) - 1;

  while (*p == '0' && Format->sharp != 1) {
    *p-- = '\0';
  }
  if (*p == '.' && Format->sharp != 1) {
    *p = '\0';
  }

  return str;
}

char *lf2str(char *str, long double number, format_sprintf *Format) {
  if (Format->tolerance < 0) Format->tolerance = 6;
  ld2a(str, number, Format);
  return str;
}

char *specS(char *str, va_list *argList, format_sprintf *Format) {
  wchar_t *pw = s21_NULL;
  char *p = s21_NULL;

  switch (Format->len) {
    case 'l':
      pw = va_arg(*argList, wchar_t *);
      if (!pw) {
        if (Format->tolerance < 6)
          s21_strncat(str, "(null)", Format->tolerance);
        else
          s21_strcat(str, "(null)");
      } else {
        wch2str(str, pw, Format->tolerance > -1 ? Format->tolerance : 0);
      }
      break;
    default:
      p = va_arg(*argList, char *);
      if (!p) {
        if (Format->tolerance < 6)
          s21_strncat(str, "(null)", Format->tolerance);
        else
          s21_strcat(str, "(null)");
      } else {
        if (Format->tolerance > -1)
          s21_strncat(str, p, Format->tolerance);
        else
          s21_strcat(str, p);
      }
  }
  ll_width_flag(str, Format);
  return str;
}

char *specC(char *str, va_list *argList, format_sprintf *Format) {
  wchar_t wchar;
  wchar_t wchar_s[10] = {0};
  switch (Format->len) {
    case 'l':
      wchar = va_arg(*argList, wchar_t);
      wchar_s[0] = wchar;
      wch2str(str, wchar_s, 0);
      break;
    default:
      str[0] = va_arg(*argList, int);
      str[1] = '\0';
  }
  ll_width_flag(str, Format);
  return str;
}

char *specu(char *str, va_list *argList, format_sprintf *Format) {
  unsigned short us_number;
  unsigned long ul_number;
  unsigned int u_number;

  switch (Format->len) {
    case 'h':
      us_number = (unsigned short)va_arg(*argList, unsigned int);
      ll2str(str, us_number);
      break;
    case 'l':
      ul_number = (unsigned long)va_arg(*argList, unsigned long);
      ul2str(str, ul_number);
      break;
    default:
      u_number = (unsigned int)va_arg(*argList, unsigned int);
      ll2str(str, u_number);
  }

  ll_tolerance(str, Format);
  signflag(str, Format);
  ll_width_flag(str, Format);
  return str;
}

char *specd(char *str, va_list *argList, format_sprintf *Format) {
  long int ld_number;
  short int sd_number;
  int number;

  switch (Format->len) {
    case 'h':
      sd_number = (short int)va_arg(*argList, int);
      ll2str(str, sd_number);
      break;
    case 'l':
      ld_number = (long int)va_arg(*argList, long int);
      ll2str(str, ld_number);
      break;
    default:
      number = va_arg(*argList, int);
      ll2str(str, number);
  }
  ll_tolerance(str, Format);
  signflag(str, Format);
  ll_width_flag(str, Format);
  return str;
}

char *speco(char *str, va_list *argList, format_sprintf *Format) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (Format->len) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*argList, unsigned int);
      ol2str(str, sd_number, Format->sharp);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*argList, unsigned long int);
      ol2str(str, ld_number, Format->sharp);
      break;
    default:
      number = va_arg(*argList, unsigned int);
      ol2str(str, number, Format->sharp);
  }
  ll_tolerance(str, Format);
  signflag(str, Format);
  ll_width_flag(str, Format);
  return str;
}

char *specxX(char *str, va_list *argList, format_sprintf *Format) {
  unsigned long int ld_number;
  unsigned short int sd_number;
  unsigned int number;

  switch (Format->len) {
    case 'h':
      sd_number = (short unsigned int)va_arg(*argList, unsigned int);
      hl2str(str, sd_number, Format);
      break;
    case 'l':
      ld_number = (long unsigned int)va_arg(*argList, unsigned long int);
      hl2str(str, ld_number, Format);
      break;
    default:
      number = (unsigned int)va_arg(*argList, unsigned int);
      hl2str(str, number, Format);
  }
  ll_tolerance(str, Format);
  signflag(str, Format);
  ll_width_flag(str, Format);

  return str;
}

char *lf_width_flag(char *str, format_sprintf *Format) {
  int str_len = (int)s21_strlen(str);
  char *p = s21_NULL, *p2 = s21_NULL;
  p2 = str;
  if (Format->width > (int)str_len) {
    char *num_str = calloc(1000 + Format->width + 2, sizeof(char));
    if (num_str) {
      p = num_str;
      if (!is_digit(*p2) && Format->zero) {
        *(p++) = *(p2++);
      }
      for (int i = 0; i < Format->width; i++) {
        if (Format->minus) {
          if (i < str_len) {
            *(p++) = *(p2++);
          } else {
            if (Format->zero)
              *(p++) = '0';
            else
              *(p++) = ' ';
          }
        } else {
          if (i < Format->width - str_len) {
            if (Format->zero)
              *(p++) = '0';
            else
              *(p++) = ' ';
          } else {
            *(p++) = *(p2++);
          }
        }
      }
      num_str[Format->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

char *ll_width_flag(char *str, format_sprintf *Format) {
  int str_len = (int)s21_strlen(str);
  if (Format->width > (int)str_len) {
    char *num_str = calloc(1000 + Format->width + 2, sizeof(char));
    if (num_str) {
      for (int i = 0; i < Format->width; i++) {
        if (Format->minus) {
          if (i < str_len) {
            num_str[i] = str[i];
          } else {
            num_str[i] = ' ';
          }
        } else {
          if (i < Format->width - str_len) {
            num_str[i] = ' ';
          } else {
            num_str[i] = str[i - (Format->width - str_len)];
          }
        }
      }
      num_str[Format->width] = '\0';
      str = s21_strcpy(str, num_str);
      free(num_str);
    }
  }
  return str;
}

char *wch2str(char *str, wchar_t *wstr, s21_size_t len) {
  s21_size_t str_len = s21_strlen(str);
  int cnt = len;
  char *p = str + str_len;

  while (*wstr != '\0' && (cnt-- > 0 || len == 0)) {
    *(p++) = (char)*(wstr++);
  }
  *p = '\0';
  return str;
}

char *signflag(char *str, format_sprintf *Format) {
  if (is_digit(*str) || *str == 'i') {
    char num_str[2] = "";
    char *p = s21_NULL;
    p = num_str;
    if (Format->plus)
      *(p++) = '+';
    else if (Format->space)
      *(p++) = ' ';
    *p = '\0';
    reverse_str(str);
    s21_strcat(str, num_str);
    reverse_str(str);
  }
  return str;
}

char *ll_tolerance(char *str, format_sprintf *Format) {
  char *num_str = calloc(1000 + Format->width + 2, sizeof(char));
  if (num_str) {
    s21_size_t str_len = s21_strlen(str);
    int shift;
    char *p = s21_NULL;
    char *s = s21_NULL;
    p = num_str;
    s = str;

    int sign = *s == '-' ? -1 : 0;
    if (Format->zero)
      Format->tolerance = (Format->tolerance > Format->width)
                              ? Format->tolerance
                              : Format->width;

    Format->tolerance = Format->tolerance > (int)str_len + sign
                            ? Format->tolerance
                            : (int)str_len + sign;
    shift = Format->spec == 'x' && Format->sharp ? 32 : 0;

    reverse_str(str);
    for (int i = 0; i < Format->tolerance; i++) {
      if (i < (int)str_len + sign)
        *(p++) = *(s++);
      else
        *(p++) = '0';
    }

    if (Format->sharp && Format->spec == (char)('X' + shift)) {
      *(p++) = (char)('X' + shift);
      *(p++) = '0';
    }

    if (sign < 0) *(p++) = '-';
    *p = '\0';
    reverse_str(num_str);
    s21_strcpy(str, num_str);
    free(num_str);
  }
  return str;
}

char *ll2str(char *str, long long number) {
  char *p = s21_NULL;
  int flag = 1, sign;

  sign = number < 0 ? -1 : 1;
  number *= sign;
  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (sign < 0) {
    *(p++) = '-';
  }
  *p = '\0';
  reverse_str(str);
  return str;
}

char *ul2str(char *str, unsigned long long number) {
  char *p = s21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    int digit;
    if (number >= 10) {
      digit = (int)(number % 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }
  *p = '\0';
  reverse_str(str);
  return str;
}

char *ol2str(char *str, unsigned long long number, int prefix) {
  char *p = s21_NULL;
  int flag = 1;

  p = str;

  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(p++) = (char)(digit + '0');
  }

  if (prefix) *(p++) = '0';
  *p = '\0';
  reverse_str(str);
  return str;
}

char *hl2str(char *str, unsigned long long number, format_sprintf *Format) {
  char *p = s21_NULL;
  int flag = 1, shift;

  p = str;

  shift = Format->spec == 'x' ? 32 : 0;

  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(p++) = (char)(digit + '0');
    else
      *(p++) = (char)(digit + 'A' + shift - 10);
  }
  *p = '\0';
  reverse_str(str);
  return str;
}

char *str2int(const char *format, int *number, va_list *argList) {
  *number = 0;
  while (is_digit(*format)) {
    *number = *format - '0' + *number * 10;
    format++;
  }
  if (*format == '*') {
    *number = va_arg(*argList, int);
    format++;
  }
  return (char *)format;
}

char *reverse_str(char *str) {
  s21_size_t str_len = s21_strlen(str);
  char ch;
  for (s21_size_t i = 0; i < str_len / 2; i++) {
    ch = str[i];
    str[i] = str[str_len - 1 - i];
    str[str_len - 1 - i] = ch;
  }
  return str;
}

long double myround(long double x, int tolerance) {
  long double right = 0.0;
  long double x1 = modfl(fabsl(x), &right);
  int mul = 0;
  int sign = signbit(x) == 0 ? 1 : -1;
  for (int i = 0; i < tolerance; i++) mul--;

  if (roundl(x1 / powl(10, mul)) > truncl(x1 / powl(10, mul))) {
    x = x + (5 * powl(10, mul - 1)) * sign;
  }
  if (tolerance <= 6 && x1 > 0) {
    x = x / powl(10, mul);
    x = truncl(x) * powl(10, mul);
  }
  return x;
}

char *ld2a(char *str, long double number, format_sprintf *Format) {
  char num1_str[1000] = "", *p1 = s21_NULL;
  p1 = num1_str;
  char num2_str[1000] = "", *p2 = s21_NULL;
  p2 = num2_str;
  long double mantis, right = 0.0L, pow = 1.0L, pow_t = 1.0L;
  int sign;
  sign = signbit(number) == 0 ? 1 : -1;

  if (fpclassify(number) < 4) {
    dclass2str(num1_str, number, Format->tolerance);
    if (sign < 0 && fpclassify(number) != 1) s21_strcat(str, "-");
    s21_strcat(str, num1_str);
    Format->zero = 0;
  } else {
    number = myround(number, Format->tolerance);
    mantis = modfl(fabsl(number), &right);

    while (truncl(right / pow) > 0) {
      int digit;
      digit = (int)truncl(fmodl(truncl(right), pow * (long double)10L) / (pow));
      *(p1++) = (char)(digit + '0');
      pow *= 10L;
    }

    if (sign < 0) *(p1++) = '-';
    *p1 = '\0';

    for (int i = 0; i < Format->tolerance; i++) pow_t *= 10;

    mantis = roundl(mantis * pow_t);
    pow = 1.0L;
    while (pow < pow_t) {
      int digit;
      digit =
          (int)truncl(fmodl(truncl(mantis), pow * (long double)10L) / (pow));
      *(p2++) = (char)(digit + '0');
      pow *= 10L;
    }
    *p2 = '\0';
    reverse_str(num1_str);
    if (s21_strlen(num1_str) == 0) s21_strcat(str, "0");
    s21_strcat(str, num1_str);
    if (Format->tolerance > 0 || Format->sharp) s21_strcat(str, ".");
    if (Format->tolerance > 0) {
      reverse_str(num2_str);
      s21_strcat(str, num2_str);
    }
  }
  return str;
}

char *dclass2str(char *str, long double x, int tolerance) {
  switch (fpclassify(x)) {
    case FP_NAN:
      s21_strcat(str, "nan");
      break;
    case FP_INFINITE:
      s21_strcat(str, "inf");
      break;
    case FP_ZERO:
      s21_strcat(str, "0");
      if (tolerance > 0) {
        s21_strcat(str, ".");
        while (tolerance--) s21_strcat(str, "0");
      }
      break;
  }
  return str;
}
