#include "s21_string.h"
/* Функция memchr ищет вхождение в массив (область памяти) символа, код которого
задан аргументом c, сравнивая каждый байт массива (области памяти)
определенный как unsigned char с кодом искомого символа. Если искомый символ
найден, то возвращается адрес найденного символа и сравнение завершается.
Если, после проверки n байтов, искомый символ не найден, то сравнение
прекращается и функция возвращает NULL.
 */

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned const char *search_str;
  search_str = str;
  void *res = s21_NULL;

  for (s21_size_t i = 0; i < n; i++) {
    if (search_str[i] == c) {
      res = (void *)(search_str + i);
      break;
    }
  }
  return res;
}

// int main() {
//   unsigned char str[8] = "help me";
//   char *sym1;
//   char *sym2;
//   sym1 = memchr(str, 'e', 8);
//   sym2 = s21_memchr(str, 'e', 8);
//   printf("%p %s\n", memchr(str, 'e', 8), sym1);
//   printf("%p %s\n", s21_memchr(str, 'e', 8), sym2);
//   return 0;
// }
