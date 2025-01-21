#include "s21_string.h"

void *s21_to_upper(const char *str) {
  int str_len = s21_strlen(str);
  char *new_str = S21_NULL;
  if (str_len > 0) {
    new_str = malloc((str_len + 1) * sizeof(char));
    int i = 0;
    for (; i < str_len; i++) {
      char a = str[i];
      if (a >= 'a' && a <= 'z') a -= 32;
      new_str[i] = a;
    }
    new_str[i] = '\0';
  }
  return new_str;
}

void *s21_to_lower(const char *str) {
  int str_len = s21_strlen(str);
  char *new_str = S21_NULL;
  if (str_len > 0) {
    new_str = malloc((str_len + 1) * sizeof(char));
    int i = 0;
    for (; i < str_len; i++) {
      char a = str[i];
      if (a >= 'A' && a <= 'Z') a += 32;
      new_str[i] = a;
    }
    new_str[i] = '\0';
  }
  return new_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int str_len = s21_strlen(str);
  int src_len = s21_strlen(src);
  int sum_len = str_len + src_len;
  char *new_str = S21_NULL;
  if (sum_len > 0) {
    new_str = calloc(sum_len + 1, sizeof(char));

    s21_strncat(new_str, src, start_index);
    s21_strncat(new_str, str, str_len);
    s21_strncat(new_str, src + start_index, src_len - start_index);
    new_str[sum_len] = '\0';
  }

  return new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  int index = 0;
  int index_reverse = s21_strlen(src) - 1;
  while (s21_strchr(trim_chars, src[index]) != S21_NULL) {
    index++;
  }
  while (s21_strchr(trim_chars, src[index_reverse]) != S21_NULL) {
    index_reverse--;
  }
  char *new_str = calloc(index_reverse - index, sizeof(char) + 1);
  s21_memcpy(new_str, src + index, index_reverse - index + 1);
  return new_str;
}