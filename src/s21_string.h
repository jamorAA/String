#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_

#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define s21_size_t unsigned long long
#define s21_NULL ((void *)0)
#define MAX_NUMBER_OF_DIGITS_IN_LONG 10
#define EXP 0.000000000001L

#define is_flag(ch) \
  ((ch) == '-' || (ch) == '+' || (ch) == ' ' || (ch) == '#' || (ch) == '0')

#define is_len(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_octal_digit(ch) ((ch) >= '0' && (ch) <= '7')

#define is_hex_digit(ch)                                                      \
  (((ch) >= '0' && (ch) <= '9') || (ch) == 'a' || (ch) == 'b' ||              \
   (ch) == 'c' || (ch) == 'd' || (ch) == 'e' || (ch) == 'f' || (ch) == 'A' || \
   (ch) == 'B' || (ch) == 'C' || (ch) == 'D' || (ch) == 'E' || (ch) == 'F')

#define is_spec(ch)                                                           \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'f' || (ch) == 's' || \
   (ch) == 'u' || (ch) == '%' || (ch) == 'g' || (ch) == 'G' || (ch) == 'e' || \
   (ch) == 'E' || (ch) == 'x' || (ch) == 'X' || (ch) == 'o' || (ch) == 'n' || \
   (ch) == 'p')

#define EPS 1E-6

typedef struct Format {
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int flag_error;
  int width;
  int tolerance;
  char len;
  char spec;
} format_sprintf;

int s21_sprintf(char *str, const char *format, ...);
void setflag(format_sprintf *Format, const char *format);
char *format_param2str(char *str, s21_size_t *str_len, format_sprintf *Format,
                       va_list *argList);
void specn(s21_size_t const *str_len, va_list *argList);
char *specPrec(char *str, format_sprintf *Format);
char *specp(char *str, va_list *argList, format_sprintf *Format);
char *specf(char *str, va_list *argList, format_sprintf *Format);
char *speceE(char *str, va_list *argList, format_sprintf *Format);
char *specgG(char *str, va_list *argList, format_sprintf *Format);
char *leE2str(char *str, long double number, format_sprintf *Format);
char *lgG2str(char *str, long double number, format_sprintf *Format);
char *lf2str(char *str, long double number, format_sprintf *Format);
char *specS(char *str, va_list *argList, format_sprintf *Format);
char *specC(char *str, va_list *argList, format_sprintf *Format);
char *specu(char *str, va_list *argList, format_sprintf *Format);
char *specd(char *str, va_list *argList, format_sprintf *Format);
char *speco(char *str, va_list *argList, format_sprintf *Format);
char *specxX(char *str, va_list *argList, format_sprintf *Format);
char *lf_width_flag(char *str, format_sprintf *Format);
char *ll_width_flag(char *str, format_sprintf *Format);
char *wch2str(char *str, wchar_t *wstr, s21_size_t len);
char *signflag(char *str, format_sprintf *Format);
char *ll_tolerance(char *str, format_sprintf *Format);
char *ll2str(char *str, long long number);
char *ul2str(char *str, unsigned long long number);
char *ol2str(char *str, unsigned long long number, int prefix);
char *hl2str(char *str, unsigned long long number, format_sprintf *Format);
char *str2int(const char *format, int *number, va_list *argList);
char *reverse_str(char *str);
long double myround(long double x, int tolerance);
char *ld2a(char *str, long double number, format_sprintf *Format);
char *dclass2str(char *str, long double x, int tolerance);

enum length { none, h, l, L };

enum specifier { c, d, i, e, E, f, g, G, o, s, u, x, X, p, n, percent };

enum base { OCT = 8, DEC = 10, HEX = 16 };

struct form {
  bool haveAsterisk;
  unsigned long width;
  enum length len;
  enum specifier spec;
};

int s21_sscanf(const char *str, const char *format, ...);
const char *formatParse(const char *format, struct form *ptr);
const char *integerParse(const char *str, const char *parseStr,
                         struct form *parseSpecifier, char **tempStr);
const char *strParse(const char *first, const char *str, char *parseStr,
                     struct form *parseSpecifier);
void prisv(const char *str, const struct form *specifier, void *address);
unsigned long long s21_atoull(const char *str, enum base b);
long double s21_atold(const char *strSrc);
const char *delete0sym(const char *str);
int getIndex(const char *str, const char *need);
char s21_tolower(char ch);

/* Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
байтах строки, на которую указывает аргумент str.*/
void *s21_memchr(const void *str, int c, s21_size_t n);

/* Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
которую указывает аргумент str.*/
char *s21_strchr(const char *str, int c);

/* Находит первый символ в строке str1, который соответствует любому символу,
указанному в str2.*/
char *s21_strpbrk(const char *base_str, const char *search_str);

/* Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
которую указывает аргумент str.*/
char *s21_strrchr(const char *str, int c);

/* Находит первое вхождение всей строки needle (не включая завершающий
нулевой символ), которая появляется в строке haystack.*/
char *s21_strstr(const char *haystack, const char *needle);

void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void s21_trim_left(const char **src, const char *trim_chars, size_t *src_length,
                   const size_t trim_chars_length);
void s21_trim_right(const char **src, const char *trim_chars,
                    size_t *src_length, const size_t trim_chars_length);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
int s21_memcmp(const void *string1, const void *string2, s21_size_t lenght);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, size_t n);

s21_size_t s21_strlen(const char *str);
s21_size_t s21_strspn(const char *str1, const char *str2);
s21_size_t s21_strcspn(const char *str1, const char *str2);
int s21_sprintf(char *str, const char *format, ...);

char *s21_strcat(char *dest, const char *src);
char *s21_strerror(int errnum);
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strtok(char *str, const char *delim);

void *s21_memcpy(void *destptr, const void *srcptr, s21_size_t num);
void *s21_memmove(void *destptr, const void *srcptr, s21_size_t num);
void *s21_memset(void *destptr, int c, s21_size_t num);
char *s21_strncpy(char *destptr, const char *srcptr, s21_size_t num);
char *s21_strcpy(char *destptr, const char *srcptr);

#if defined(__linux__)
#define std 0
#define N_ERR 133
#define ERR_LIST                                        \
  {"Success",                                           \
   "Operation not permitted",                           \
   "No such file or directory",                         \
   "No such process",                                   \
   "Interrupted system call",                           \
   "Input/output error",                                \
   "No such device or address",                         \
   "Argument list too long",                            \
   "Exec format error",                                 \
   "Bad file descriptor",                               \
   "No child processes",                                \
   "Resource temporarily unavailable",                  \
   "Cannot allocate memory",                            \
   "Permission denied",                                 \
   "Bad address",                                       \
   "Block device required",                             \
   "Device or resource busy",                           \
   "File exists",                                       \
   "Invalid cross-device link",                         \
   "No such device",                                    \
   "Not a directory",                                   \
   "Is a directory",                                    \
   "Invalid argument",                                  \
   "Too many open files in system",                     \
   "Too many open files",                               \
   "Inappropriate ioctl for device",                    \
   "Text file busy",                                    \
   "File too large",                                    \
   "No space left on device",                           \
   "Illegal seek",                                      \
   "Read-only file system",                             \
   "Too many links",                                    \
   "Broken pipe",                                       \
   "Numerical argument out of domain",                  \
   "Numerical result out of range",                     \
   "Resource deadlock avoided",                         \
   "File name too long",                                \
   "No locks available",                                \
   "Function not implemented",                          \
   "Directory not empty",                               \
   "Too many levels of symbolic links",                 \
   "Unknown error 41",                                  \
   "No message of desired type",                        \
   "Identifier removed",                                \
   "Channel number out of range",                       \
   "Level 2 not synchronized",                          \
   "Level 3 halted",                                    \
   "Level 3 reset",                                     \
   "Link number out of range",                          \
   "Protocol driver not attached",                      \
   "No CSI structure available",                        \
   "Level 2 halted",                                    \
   "Invalid exchange",                                  \
   "Invalid request descriptor",                        \
   "Exchange full",                                     \
   "No anode",                                          \
   "Invalid request code",                              \
   "Invalid slot",                                      \
   "Unknown error 58",                                  \
   "Bad font file format",                              \
   "Device not a stream",                               \
   "No data available",                                 \
   "Timer expired",                                     \
   "Out of streams resources",                          \
   "Machine is not on the network",                     \
   "Package not installed",                             \
   "Object is remote",                                  \
   "Link has been severed",                             \
   "Advertise error",                                   \
   "Srmount error",                                     \
   "Communication error on send",                       \
   "Protocol error",                                    \
   "Multihop attempted",                                \
   "RFS specific error",                                \
   "Bad message",                                       \
   "Value too large for defined data type",             \
   "Name not unique on network",                        \
   "File descriptor in bad state",                      \
   "Remote address changed",                            \
   "Can not access a needed shared library",            \
   "Accessing a corrupted shared library",              \
   ".lib section in a.out corrupted",                   \
   "Attempting to link in too many shared libraries",   \
   "Cannot exec a shared library directly",             \
   "Invalid or incomplete multibyte or wide character", \
   "Interrupted system call should be restarted",       \
   "Streams pipe error",                                \
   "Too many users",                                    \
   "Socket operation on non-socket",                    \
   "Destination address required",                      \
   "Message too long",                                  \
   "Protocol wrong type for socket",                    \
   "Protocol not available",                            \
   "Protocol not supported",                            \
   "Socket type not supported",                         \
   "Operation not supported",                           \
   "Protocol family not supported",                     \
   "Address family not supported by protocol",          \
   "Address already in use",                            \
   "Cannot assign requested address",                   \
   "Network is down",                                   \
   "Network is unreachable",                            \
   "Network dropped connection on reset",               \
   "Software caused connection abort",                  \
   "Connection reset by peer",                          \
   "No buffer space available",                         \
   "Transport endpoint is already connected",           \
   "Transport endpoint is not connected",               \
   "Cannot send after transport endpoint shutdown",     \
   "Too many references: cannot splice",                \
   "Connection timed out",                              \
   "Connection refused",                                \
   "Host is down",                                      \
   "No route to host",                                  \
   "Operation already in progress",                     \
   "Operation now in progress",                         \
   "Stale file handle",                                 \
   "Structure needs cleaning",                          \
   "Not a XENIX named type file",                       \
   "No XENIX semaphores available",                     \
   "Is a named type file",                              \
   "Remote I/O error",                                  \
   "Disk quota exceeded",                               \
   "No medium found",                                   \
   "Wrong medium type",                                 \
   "Operation canceled",                                \
   "Required key not available",                        \
   "Key has expired",                                   \
   "Key has been revoked",                              \
   "Key was rejected by service",                       \
   "Owner died",                                        \
   "State not recoverable",                             \
   "Operation not possible due to RF-kill",             \
   "Memory page has hardware error"};

#endif

#if defined(__APPLE__)
#define std 1
#define N_ERR 107
#define ERR_LIST                                      \
  {"Undefined error: 0",                              \
   "Operation not permitted",                         \
   "No such file or directory",                       \
   "No such process",                                 \
   "Interrupted system call",                         \
   "Input/output error",                              \
   "Device not configured",                           \
   "Argument list too long",                          \
   "Exec format error",                               \
   "Bad file descriptor",                             \
   "No child processes",                              \
   "Resource deadlock avoided",                       \
   "Cannot allocate memory",                          \
   "Permission denied",                               \
   "Bad address",                                     \
   "Block device required",                           \
   "Resource busy",                                   \
   "File exists",                                     \
   "Cross-device link",                               \
   "Operation not supported by device",               \
   "Not a directory",                                 \
   "Is a directory",                                  \
   "Invalid argument",                                \
   "Too many open files in system",                   \
   "Too many open files",                             \
   "Inappropriate ioctl for device",                  \
   "Text file busy",                                  \
   "File too large",                                  \
   "No space left on device",                         \
   "Illegal seek",                                    \
   "Read-only file system",                           \
   "Too many links",                                  \
   "Broken pipe",                                     \
   "Numerical argument out of domain",                \
   "Result too large",                                \
   "Resource temporarily unavailable",                \
   "Operation now in progress",                       \
   "Operation already in progress",                   \
   "Socket operation on non-socket",                  \
   "Destination address required",                    \
   "Message too long",                                \
   "Protocol wrong type for socket",                  \
   "Protocol not available",                          \
   "Protocol not supported",                          \
   "Socket type not supported",                       \
   "Operation not supported",                         \
   "Protocol family not supported",                   \
   "Address family not supported by protocol family", \
   "Address already in use",                          \
   "Can't assign requested address",                  \
   "Network is down",                                 \
   "Network is unreachable",                          \
   "Network dropped connection on reset",             \
   "Software caused connection abort",                \
   "Connection reset by peer",                        \
   "No buffer space available",                       \
   "Socket is already connected",                     \
   "Socket is not connected",                         \
   "Can\'t send after socket shutdown",               \
   "Too many references: can\'t splice",              \
   "Operation timed out",                             \
   "Connection refused",                              \
   "Too many levels of symbolic links",               \
   "File name too long",                              \
   "Host is down",                                    \
   "No route to host",                                \
   "Directory not empty",                             \
   "Too many processes",                              \
   "Too many users",                                  \
   "Disc quota exceeded",                             \
   "Stale NFS file handle",                           \
   "Too many levels of remote in path",               \
   "RPC struct is bad",                               \
   "RPC version wrong",                               \
   "RPC prog. not avail",                             \
   "Program version wrong",                           \
   "Bad procedure for program",                       \
   "No locks available",                              \
   "Function not implemented",                        \
   "Inappropriate file type or format",               \
   "Authentication error",                            \
   "Need authenticator",                              \
   "Device power is off",                             \
   "Device error",                                    \
   "Value too large to be stored in data type",       \
   "Bad executable (or shared library)",              \
   "Bad CPU type in executable",                      \
   "Shared library version mismatch",                 \
   "Malformed Mach-o file",                           \
   "Operation canceled",                              \
   "Identifier removed",                              \
   "No message of desired type",                      \
   "Illegal byte sequence",                           \
   "Attribute not found",                             \
   "Bad message",                                     \
   "EMULTIHOP (Reserved)",                            \
   "No message available on STREAM",                  \
   "ENOLINK (Reserved)",                              \
   "No STREAM resources",                             \
   "Not a STREAM",                                    \
   "Protocol error",                                  \
   "STREAM ioctl timeout",                            \
   "Operation not supported on socket",               \
   "Policy not found",                                \
   "State not recoverable",                           \
   "Previous owner died",                             \
   "Interface output queue is full"};

#endif

#endif  // SRC_S21_STRING_H_
