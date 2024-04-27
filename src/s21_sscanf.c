#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  const char *first = str;
  struct form tempSpecifier;
  bool flag = 1;
  char *tempStr = (char *)malloc(sizeof(char) * s21_strlen(first) + 4);
  if (!tempStr) flag = 0;
  va_list temp;
  va_start(temp, format);
  void *address;
  int total = 0;
  if (!(*str)) total = -1;
  while (*format && *str && flag) {
    if (*format == ' ' || *format == '\t' || *format == '\n') {
      while (*format == ' ' || *format == '\t' || *format == '\n') format++;
      while (*str == ' ' || *str == '\t' || *str == '\n') str++;
    } else if (*format == '%') {
      format = formatParse(format + 1, &tempSpecifier);
      str = strParse(first, str, tempStr, &tempSpecifier);
      if (tempSpecifier.haveAsterisk ||
          (tempSpecifier.spec == percent && s21_strlen(tempStr) == 1 &&
           *tempStr == '%'))
        continue;
      if (!s21_strlen(tempStr)) flag = 0;
      if (flag) {
        address = va_arg(temp, void *);
        prisv(tempStr, &tempSpecifier, address);
        if (tempSpecifier.spec != n) total++;
      }
    } else {
      if (*format == *str)
        format++, str++;
      else
        flag = 0;
    }
  }
  va_end(temp);
  if (tempStr) free(tempStr);
  return total;
}

const char *strParse(const char *first, const char *str, char *parseStr,
                     struct form *parseSpecifier) {
  char *tempStr = parseStr;
  *tempStr = '\0';
  unsigned long sum = 0;
  if (parseSpecifier->spec == c) {
    *tempStr++ = *str++;
  } else if (parseSpecifier->spec == n) {
    int num = (int)(str - first);
    for (int i = 100000000; i != 0; i /= 10)
      if (num > i) *tempStr++ = '0';
    *tempStr = '\0';
    while (num != 0) {
      *(--tempStr) = (char)('0' + num % 10);
      num /= 10;
    }
    while (*tempStr) tempStr++;
  } else {
    while (*str == ' ' || *str == '\t' || *str == '\n') str++;
    if (parseSpecifier->spec >= e && parseSpecifier->spec <= G) {
      bool flag = 1;
      while (*str && (s21_strchr("+-.eE0123456789", *str)) &&
             (++sum <= parseSpecifier->width || parseSpecifier->width == 0) &&
             flag) {
        if ((*str == '.' &&
             (s21_strchr(parseStr, 'e') || s21_strchr(parseStr, 'E'))) ||
            ((*str == '.' || *str == 'e' || *str == 'E') &&
             s21_strchr(parseStr, s21_tolower(*str))) ||
            ((*str == 'e' || *str == 'E' ||
              (*str == '.' && !s21_strchr("0123456789", *(str + 1)))) &&
             tempStr == parseStr) ||
            ((*str == '-' || *str == '+') &&
             !((*(str + 1) >= '0' && *(str + 1) <= '9' &&
                !s21_strlen(parseStr)) ||
               (s21_strlen(parseStr) > 1 &&
                (*(str - 1) == 'e' || *(str - 1) == 'E'))))) {
          flag = 0;
        } else {
          *tempStr++ = (char)s21_tolower(*str++);
          *tempStr = '\0';
        }
      }
    } else if (parseSpecifier->spec == s) {
      while (*str && !s21_strchr(" \t\n", *str) &&
             (++sum <= parseSpecifier->width || parseSpecifier->width == 0))
        *tempStr++ = *str++;
    } else if (parseSpecifier->spec == percent) {
      if (*str == '%') *tempStr++ = *str++;
    } else {
      str = integerParse(str, parseStr, parseSpecifier, &tempStr);
    }
  }
  *tempStr = '\0';
  return str;
}

const char *integerParse(const char *str, const char *parseStr,
                         struct form *parseSpecifier, char **tempStr) {
  unsigned long sum = 0;
  if ((*str == '-' || *str == '+') &&
      (++sum <= parseSpecifier->width || parseSpecifier->width == 0)) {
    if (s21_strlen(str) > 1 &&
        ((!s21_strchr("0123456789abcdefABCDEF", *(str + 1)) &&
          (parseSpecifier->spec == x || parseSpecifier->spec == X ||
           parseSpecifier->spec == p)) ||
         (!s21_strchr("01234567", *(str + 1)) && parseSpecifier->spec == o) ||
         (!s21_strchr("0123456789", *(str + 1)) &&
          (parseSpecifier->spec == d || parseSpecifier->spec == u ||
           parseSpecifier->spec == i))))
      parseSpecifier->spec = c;
    else
      *(*tempStr)++ = *str++;
  }
  if (parseSpecifier->spec == x || parseSpecifier->spec == X ||
      parseSpecifier->spec == p ||
      (parseSpecifier->spec == i && s21_strlen(str) >= 3 && *str == '0' &&
       s21_strchr("Xx", *(str + 1)) &&
       s21_strchr("0123456789abcdefABCDEF", *(str + 2)))) {
    if (s21_strlen(str) >= 3 && *str == '0' && s21_strchr("Xx", *(str + 1)) &&
        s21_strchr("0123456789abcdefABCDEF", *(str + 2)) &&
        (parseSpecifier->width == 0 || parseSpecifier->width > 2))
      str += 2, sum += 2;
    *(*tempStr)++ = '0';
    *(*tempStr)++ = 'x';
    while (*str && s21_strchr("0123456789abcdefABCDEF", *str) &&
           (++sum <= parseSpecifier->width || parseSpecifier->width == 0))
      *(*tempStr)++ = *str++;
    if (*(*tempStr - 1) == 'x') *tempStr -= 2;
  } else if (parseSpecifier->spec == o ||
             (parseSpecifier->spec == i && s21_strlen(str) >= 2 &&
              *str == '0' && s21_strchr("0123456789", *(str + 1)))) {
    if (s21_strlen(str) >= 2 && *str == '0' &&
        s21_strchr("01234567", *(str + 1)) &&
        (parseSpecifier->width == 0 || parseSpecifier->width > 1))
      str++, sum++;
    *(*tempStr)++ = '0';
    while (*str && s21_strchr("01234567", *str) &&
           (++sum <= parseSpecifier->width || parseSpecifier->width == 0))
      *(*tempStr)++ = *str++;
    **tempStr = '\0';
    if (s21_strlen(parseStr) == 1) *(--(*tempStr)) = '\0';
  } else if (parseSpecifier->spec == d || parseSpecifier->spec == u ||
             parseSpecifier->spec == i) {
    while (*str && s21_strchr("0123456789", *str) &&
           (++sum <= parseSpecifier->width || parseSpecifier->width == 0))
      *(*tempStr)++ = *str++;
  }
  return str;
}

const char *formatParse(const char *format, struct form *ptr) {
  char widthStr[MAX_NUMBER_OF_DIGITS_IN_LONG + 1];
  char ch = *format;
  if (ch == '*') {
    ptr->haveAsterisk = 1;
    ch = *(++format);
  } else {
    ptr->haveAsterisk = 0;
  }
  while (ch == '0') ch = *(++format);
  int j;
  for (j = 0; ch >= '0' && ch <= '9'; j++, ch = *(++format)) widthStr[j] = ch;
  widthStr[j] = '\0';
  if (s21_strlen(widthStr) > 0) {
    unsigned long width = s21_atoull(widthStr, DEC);
    ptr->width = width;
  } else {
    ptr->width = 0;
  }
  switch (ch) {
    case 'h':
      ptr->len = h;
      break;
    case 'l':
      ptr->len = l;
      break;
    case 'L':
      ptr->len = L;
      break;
    default:
      ptr->len = none;
      break;
  }
  if (ptr->len != none) ch = *(++format);
  switch (ch) {
    case 'c':
      ptr->spec = c;
      break;
    case 'd':
      ptr->spec = d;
      break;
    case 'i':
      ptr->spec = i;
      break;
    case 'e':
      ptr->spec = e;
      break;
    case 'E':
      ptr->spec = E;
      break;
    case 'f':
      ptr->spec = f;
      break;
    case 'g':
      ptr->spec = g;
      break;
    case 'G':
      ptr->spec = G;
      break;
    case 'o':
      ptr->spec = o;
      break;
    case 's':
      ptr->spec = s;
      break;
    case 'u':
      ptr->spec = u;
      break;
    case 'x':
      ptr->spec = x;
      break;
    case 'X':
      ptr->spec = X;
      break;
    case 'p':
      ptr->spec = p;
      break;
    case 'n':
      ptr->spec = n;
      break;
    case '%':
      ptr->spec = percent;
      break;
    default:
      break;
  }
  return ++format;
}

void prisv(const char *str, const struct form *specifier, void *address) {
  if (specifier->spec == c) {
    *((char *)address) = *str;
  } else if (specifier->spec == s) {
    s21_strcpy(address, str);
  } else if (specifier->spec == x || specifier->spec == X ||
             specifier->spec == o || specifier->spec == i ||
             specifier->spec == d || specifier->spec == u ||
             specifier->spec == p || specifier->spec == n) {
    bool haveMinus = false;
    if (*str == '-' || *str == '+') {
      if (*str == '-') haveMinus = true;
      str++;
    }
    int mult = 1;
    if (haveMinus) mult = -1;
    enum base b;
    if (*str == '0' && *(str + 1) == 'x' &&
        (specifier->spec == x || specifier->spec == X || specifier->spec == p ||
         specifier->spec == i)) {
      str += 2;
      str = delete0sym(str);
      b = HEX;
    } else if (*str == '0' && (specifier->spec == o || specifier->spec == i)) {
      str++;
      str = delete0sym(str);
      b = OCT;
    } else {
      str = delete0sym(str);
      b = DEC;
    }
    if (specifier->spec == i || specifier->spec == d) {
      if (specifier->len == h)
        *((short *)address) = (short)((short)s21_atoull(str, b) * mult);
      else if (specifier->len == l)
        *((long *)address) = (long)s21_atoull(str, b) * mult;
      else if (specifier->len == none)
        *((int *)address) = (int)s21_atoull(str, b) * mult;
    } else {
      if (specifier->spec == p)
        *((unsigned long long *)address) = s21_atoull(str, b) * mult;
      else if (specifier->len == h)
        *((unsigned short *)address) =
            (unsigned short)s21_atoull(str, b) * mult;
      else if (specifier->len == l)
        *((unsigned long *)address) = (unsigned long)s21_atoull(str, b) * mult;
      else if (specifier->len == none)
        *((unsigned int *)address) = (unsigned int)s21_atoull(str, b) * mult;
    }
  } else if (specifier->spec >= e && specifier->spec <= G) {
    bool haveMinus = false;
    if (*str == '-' || *str == '+') {
      if (*str == '-') haveMinus = true;
      str++;
    }
    int mult = 1;
    if (haveMinus) mult = -1;
    str = delete0sym(str);
    if (specifier->len == none)
      *((float *)address) = (float)(s21_atold(str) * mult);
    else if (specifier->len == l)
      *((double *)address) = (double)(s21_atold(str) * mult);
    else if (specifier->len == L)
      *((long double *)address) = s21_atold(str) * mult;
  }
}

unsigned long long s21_atoull(const char *str, enum base b) {
  unsigned long long num = 0;
  if (s21_strlen(str) > 0) {
    const char *ptr = str + s21_strlen(str) - 1;
    for (int i = 0; ptr >= str; i++, ptr--)
      if (b == OCT || b == DEC || (b == HEX && *ptr >= '0' && *ptr <= '9'))
        num += (*ptr - '0') * (unsigned long long)pow(b, i);
      else if (*ptr >= 'a' && *ptr <= 'f')
        num += (*ptr - 'a' + 10) * (unsigned long long)pow(b, i);
      else
        num += (long)(*ptr - 'A' + 10) * (unsigned long long)pow(b, i);
  }
  return num;
}

long double s21_atold(const char *strSrc) {
  char *str = (char *)malloc(s21_strlen(strSrc) + 1);
  s21_strcpy(str, strSrc);
  long exp = 0;
  const char *ptr = NULL;
  if (s21_strchr(str, 'e'))
    ptr = s21_strchr(str, 'e');
  else if (s21_strchr(str, 'E'))
    ptr = s21_strchr(str, 'E');
  int minus = 1;
  if (ptr) {
    ptr++;
    if (*ptr == '-' || *ptr == '+') {
      if (*ptr == '-') minus = -1;
      ptr++;
    }
    ptr = delete0sym(ptr);
    exp = (long)(s21_atoull(ptr, DEC)) * minus;
    if (s21_strchr(str, 'e'))
      str[getIndex(str, s21_strchr(str, 'e'))] = '\0';
    else
      str[getIndex(str, s21_strchr(str, 'E'))] = '\0';
  }
  char *p;
  p = s21_strchr(str, '.');
  if (p) {
    exp -= (long)(s21_strlen(str) - getIndex(str, p) - 1);
    while (*p) {
      *p = *(p + 1);
      p++;
    }
  }
  long double num = 0;
  if (s21_strlen(str) > 0) {
    const char *pointer = str + s21_strlen(str) - 1;
    for (int i = 0; pointer >= str; i++, pointer--)
      num += (*pointer - '0') * pow(10, i);
  }
  num *= powl(10, exp);
  free(str);
  return num;
}

const char *delete0sym(const char *str) {
  while (*str == '0') str++;
  return str;
}

int getIndex(const char *str, const char *need) {
  int i = 0;
  bool flag = 1;
  while (*str && flag) {
    if (str == need) flag = 0;
    if (flag) str++, i++;
  }
  return i;
}

char s21_tolower(char ch) {
  if (ch >= 'A' && ch <= 'Z') ch = 'a' + ch - 'A';
  return ch;
}
