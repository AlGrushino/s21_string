#include "s21_string.h"

/**
 * Ищет символ c в первых n байтах той памяти, на которую указывает str,
 * возвращает поинтер на первое совпадение
 */
void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *ptr = str;
  int find = 0;
  for (s21_size_t i = 0; i < n && !find; i++) {
    int b = *(ptr++);
    if (b == c) {
      find = 1;
      ptr--;
    }
  }
  if (!find) ptr = S21_NULL;
  return (void *)ptr;
}

/**
 * Возвращает строку, описывающую ошибку
 */
char *s21_strerror(int errnum) {
  static char result[128] = "";
  static const char *strerr[] = s21_error;

  s21_memset(result, '\0', 128);

  if (errnum < 0 || errnum >= MAX_ERRLIST) {
    s21_sprintf(result, "Unknown error %d", errnum);
  } else {
    s21_strncpy(result, (char *)strerr[errnum],
                s21_strlen((char *)strerr[errnum]));
  }

  return result;
}

/**
 * Сравнивает первые n символов в str1 и str2, возвращает целое число
 */
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int rez = 0;
  char *p1 = (char *)str1;
  char *p2 = (char *)str2;
  for (s21_size_t i = 0; i < n && rez == 0; i++) {
    rez = *(p1 + i) - *(p2 + i);
  }

  return rez;
}

/**
 * Копирует n из src в dest
 */
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *p_dest = (char *)dest;
  char *p_src = (char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    *(p_dest + i) = *(p_src + i);
  }

  return dest;
}

/**
 * Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
 * указывает аргумент str
 */
void *s21_memset(void *str, int c, s21_size_t n) {
  char *p = str;

  for (s21_size_t i = 0; i < n; i++) {
    *(p + i) = c;
  }

  return str;
}

/**
 * Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest, длиной до n символов, возвращает поинтер на dest
 */
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;
  while (*ptr != '\0') ptr++;
  s21_size_t i = 0;
  for (; i < n && src[i] != '\0'; i++) {
    ptr[i] = src[i];
  }
  ptr[i] = '\0';
  return dest;
}

/**
 * Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str
 */
char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;

  while (*str != '\0' && res == S21_NULL) {
    if (c == *str) res = (char *)str;
    str++;
  }
  return res;
}

/**
 * Сравнивает не более первых n байтов str1 и str2
 */
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int rez = 0;

  for (s21_size_t i = 0; i < n && rez == 0 && *str1 != '\0' && *str2 != '\0';
       i++) {
    rez = *(str1++) - *(str2++);
  }
  return rez;
}

/**
 * Копирует до n символов из строки, на которую указывает src, в dest
 */
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n && *src != '\0'; i++) {
    *(dest++) = *(src++);
  }
  return dest;
}

/**
 * Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, не входящих в str2
 */
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  char *find = s21_strpbrk(str1, str2);
  s21_size_t max = s21_strlen(str1);

  if (find != S21_NULL) max = find - str1;

  return max;
}

/**
 * Находит первый символ в строке str1, который соответствует любому символу,
 * указанному в str2
 */
char *s21_strpbrk(const char *str1, const char *str2) {
  char *rez = S21_NULL;
  s21_size_t len = s21_strlen(str2);

  while (*str1 != '\0' && rez == S21_NULL) {
    for (s21_size_t i = 0; i < len; i++) {
      if (*(str2 + i) == *str1) rez = (char *)str1;
    }
    str1++;
  }

  return rez;
}

/**
 * Возвращает длину строки
 */
s21_size_t s21_strlen(const char *str) {
  char *ptr = (char *)str;
  while (*ptr != '\0') ptr++;
  return ptr - str;
}

/**
 * Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str
 */
char *s21_strrchr(const char *str, int c) {
  char *find = S21_NULL;

  while (*str != '\0') {
    if (c == *str) find = (char *)str;
    str++;
  }
  return find;
}

/**
 * Находит первое вхождение всей строки needle (не включая завершающий нулевой
 * символ), которая появляется в строке haystack
 */
char *s21_strstr(const char *haystack, const char *needle) {
  char *res = S21_NULL;
  char *find = s21_strchr(haystack, *needle);
  s21_size_t len = s21_strlen(needle);

  while (find != S21_NULL && res == S21_NULL) {
    if (s21_strncmp(find, needle, len) == 0) res = find;
    find = s21_strchr(find + 1, *needle);
  }
  return res;
}

/**
 * Разбивает строку str на ряд токенов, разделенных delim
 */
char *s21_strtok(char *str, const char *delim) {
  static char *old;
  char *find = S21_NULL;

  if (str == S21_NULL) str = old;

  if (str != S21_NULL) {
    find = str;
    str += s21_strcspn(str, delim);
    if (*str != '\0') {
      *str = '\0';
      old = str + 1;
    } else {
      old = S21_NULL;
    }
  }
  return find;
}
