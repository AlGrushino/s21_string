#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

START_TEST(s21_strncat_1) {
  char s21_str[10] = "abc";
  char str[10] = "abc";
  char cat[4] = "def";
  int n = 5;
  char *s21_res = s21_strncat(s21_str, cat, n);
  char *res = strncat(str, cat, n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strncat_2) {
  char s21_str[6] = "";
  char str[6] = "";
  char cat[3] = "def";
  int n = 3;
  char *s21_res = s21_strncat(s21_str, cat, n);
  char *res = strncat(str, cat, n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memchr_1) {
  char str1[] = "";
  int n = 5;
  char *s21_res = s21_memchr(str1, ' ', n);
  ck_assert_ptr_null(s21_res);
}
END_TEST

START_TEST(s21_memchr_2) {
  char str1[] = "abc";
  int n = 3;
  char *s21_res = s21_memchr(str1, 'b', n);
  char *res = memchr(str1, 'b', n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memchr_3) {
  char str1[] = "abc";
  int n = 1;
  char *s21_res = s21_memchr(str1, 'c', n);
  char *res = memchr(str1, 'c', n);
  ck_assert_ptr_null(s21_res);
}
END_TEST

START_TEST(s21_memcmp_1) {
  char str1[] = "abc";
  char str2[] = "abc";
  int n = 3;
  int s21_res = s21_memcmp(str1, str2, n);
  int res = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcmp_2) {
  char str1[] = "abc";
  char str2[] = "abc";
  int n = 1;
  int s21_res = s21_memcmp(str1, str2, n);
  int res = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcmp_3) {
  char str1[] = "abc";
  char str2[] = "abc";
  int n = 2;
  int s21_res = s21_memcmp(str1, str2, n);
  int res = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcmp_4) {
  char str1[] = "abc";
  char str2[] = "acb";
  int n = 2;
  int s21_res = s21_memcmp(str1, str2, n);
  int res = memcmp(str1, str2, n);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcpy_1) {
  char str1[6] = {0};
  char str2[6] = {0};
  char copy[4] = "copy";
  int n = 4;
  char *s21_res = s21_memcpy(str1, copy, n);
  char *res = memcpy(str2, copy, n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcpy_2) {
  char str1[6] = {0};
  char str2[6] = {0};
  char copy[4] = "copy";
  int n = 2;
  char *s21_res = s21_memcpy(str1, copy, n);
  char *res = memcpy(str2, copy, n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memcpy_3) {
  char str1[6] = {0};
  char str2[6] = {0};
  char copy[4] = "copy";
  int n = 0;
  char *s21_res = s21_memcpy(str1, copy, n);
  char *res = memcpy(str2, copy, n);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sprintf_d1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %d";
  int s21_res = s21_sprintf(s21_str, format, 0);
  int res = sprintf(str, format, 0);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_d2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: % d %hd %hhd %ld %lld";
  int s21_res = s21_sprintf(s21_str, format, 1, -1, -1, -1, -1);
  int res = sprintf(str, format, 1, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_d3) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %*.*d %10hd %10hhd %10ld %10lld";
  int s21_res = s21_sprintf(s21_str, format, 10, 2, -1, -1, -1, -1, -1);
  int res = sprintf(str, format, 10, 2, -1, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_d4) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: % 10.3d %010hd %10.3hhd %10.3ld %10.3lld";
  int s21_res = s21_sprintf(s21_str, format, -1, -1, -1, -1, -1);
  int res = sprintf(str, format, -1, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_d5) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format =
      "test: %0-+ #10.3d %0-+ #10.3hd %0-+ #10.3hhd %0-+ #10.3ld %0-+ #10.3lld";
  int s21_res = s21_sprintf(s21_str, format, -1, -1, -1, -1, -1);
  int res = sprintf(str, format, -1, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_f1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %#.0f %f %f";
  int s21_res = s21_sprintf(s21_str, format, 0.0, 0.0, 0.0);
  int res = sprintf(str, format, 0.0, 0.0, 0.0);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_f2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %f %f %f %Lf";
  int s21_res = s21_sprintf(s21_str, format, -100.0, 100.0, -0.0, 123.134L);
  int res = sprintf(str, format, -100.0, 100.0, -0.0, 123.134L);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_f3) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %0-+ #.0f %0-+ #10.0f %0-+ #010.3f %0-+ #10.3Lf";
  int s21_res = s21_sprintf(s21_str, format, -0.5, 1.5, -0.0, 123.134L);
  int res = sprintf(str, format, -0.5, 1.5, -0.0, 123.134L);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_u1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %u %hu %hhu %lu %llu";
  int s21_res = s21_sprintf(s21_str, format, -1, -1, -1, -1, -1);
  int res = sprintf(str, format, -1, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_u2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format =
      "test: %0-+# 20.6u %0-+# 20.6hu %0-+# 20.6hhu %0-+# 20.6lu %0-+# 20.6llu";
  int s21_res = s21_sprintf(s21_str, format, 0, -1, -1, -1, -1);
  int res = sprintf(str, format, 0, -1, -1, -1, -1);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_x1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %x %hhx %lx";
  int s21_res = s21_sprintf(s21_str, format, -1024, -1024, -1024);
  int res = sprintf(str, format, -1024, -1024, -1024);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_x2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %x %hx %hhx %lx %llx";
  int s21_res =
      s21_sprintf(s21_str, format, 1000000, 1000000, 1000000, 1000000, 1000000);
  int res = sprintf(str, format, 1000000, 1000000, 1000000, 1000000, 1000000);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_x3) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %-+0 #10.4X %-+0 #10.4lX %-+0 #10.4llX";
  int s21_res = s21_sprintf(s21_str, format, 100000, 1000000, 1000000);
  int res = sprintf(str, format, 100000, 1000000, 1000000);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_i1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format =
      "test: %-+0 #10i %-+0 #10.4hi %-+0 #10.4hhi %-+0 #10.4li %-+0 #10.4lli";
  int s21_res =
      s21_sprintf(s21_str, format, 1000000, 1000000, 1000000, 1000000, 1000000);
  int res = sprintf(str, format, 1000000, 1000000, 1000000, 1000000, 1000000);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_e1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %e %he %he %e %LE";
  int s21_res = s21_sprintf(s21_str, format, 0.0, 1000000.0, 1000000.0,
                            1000000.0, 1000000.0L);
  int res =
      sprintf(str, format, 0.0, 1000000.0, 1000000.0, 1000000.0, 1000000.0L);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_e2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format =
      "test: %-+0 #10.4e %-+0 #10.4he %-+0 #10.4he %-+0 #10.4E %-+0 #10.4Le";
  int s21_res = s21_sprintf(s21_str, format, 1.12345, 2.45367889, 2.45367889,
                            2.45367889, 2.45367889L);
  int res = sprintf(str, format, 1.12345, 2.45367889, 2.45367889, 2.45367889,
                    2.45367889L);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_g1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %g %hg %Lg %LG";
  int s21_res = s21_sprintf(s21_str, format, 0.002345, 0.00000112345,
                            1000000.0L, 699999999.0L);
  int res =
      sprintf(str, format, 0.002345, 0.00000112345, 1000000.0L, 699999999.0L);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_o1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %o %#ho %#lo %llo";
  int s21_res = s21_sprintf(s21_str, format, 10000, 10000, 10000, 10000);
  int res = sprintf(str, format, 10000, 10000, 10000, 10000);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_s1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "%-s %10.1s %3.4s";
  int s21_res = s21_sprintf(s21_str, format, "privet", "privet", "privet");
  int res = sprintf(str, format, "privet", "privet", "privet");
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_p1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  int a, b, c, d, e;
  const char *format = "test: %p %hp %hhp %lp %llp";
  int s21_res = s21_sprintf(s21_str, format, &a, &b, &c, &d, &e);
  int res = sprintf(str, format, &a, &b, &c, &d, &e);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_c1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %c %hc %hhc %lc %llc";
  int s21_res = s21_sprintf(s21_str, format, 'a', 'b', 'c', 'd', 'e');
  int res = sprintf(str, format, 'a', 'b', 'c', 'd', 'e');
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_c2) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  const char *format = "test: %10.4c %10.2hc %3.1hhc %4.2lc %3.6llc";
  int s21_res = s21_sprintf(s21_str, format, 'a', 'b', 'c', 'd', 'e');
  int res = sprintf(str, format, 'a', 'b', 'c', 'd', 'e');
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_n1) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  int s21_n, n;
  const char *format = "test: %n";
  int s21_res = s21_sprintf(s21_str, format, &s21_n);
  int res = sprintf(str, format, &n);
  ck_assert_str_eq(s21_str, str);
}

START_TEST(s21_sprintf_percent) {
  char s21_str[1024] = {0};
  char str[1024] = {0};
  int a, b, c, d, e;
  const char *format = "test: %%";
  int s21_res = s21_sprintf(s21_str, format, 'a', 'b', 'c', 'd', 'e');
  int res = sprintf(str, format, 'a', 'b', 'c', 'd', 'e');
  ck_assert_str_eq(s21_str, str);
}

//------------------ALYONA------------------
START_TEST(s21_memset_1) {
  char str[6] = "piskaa";
  int c = 45;
  int n = 2;
  char *s21_res = s21_memset(str, c, n);
  char *res = memset(str, c, n);
  ck_assert_ptr_eq(s21_res, res);
}
END_TEST

START_TEST(s21_memset_2) {
  char str[6] = "piskaa";
  int c = 45;
  int n = 0;
  char *s21_res = s21_memset(str, c, n);
  char *res = memset(str, c, n);
  ck_assert_ptr_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strcspn_1) {
  char s21_str1[6] = "abcdef";
  char s21_str2[3] = "edc";
  char str1[6] = "abcdef";
  char str2[3] = "edc";
  s21_size_t s21_res = s21_strcspn(s21_str1, s21_str2);
  s21_size_t res = strcspn(str1, str2);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strrchr_1) {
  const char *str = "aabaabaa";
  char find = 'b';
  char *s21_res = s21_strrchr(str, find);
  char *res = strrchr(str, find);
  ck_assert_int_eq(*s21_res, *res);
}
END_TEST

START_TEST(s21_strpbrk_1) {
  const char *s21_str1 = "abcdef";
  const char *str1 = "abcdef";
  const char *str2 = "ld";
  char *s21_res = s21_strpbrk(s21_str1, str2);
  char *res = strpbrk(str1, str2);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strlen_1) {
  const char *str = "aaaaaa";
  s21_size_t s21_res = s21_strlen(str);
  s21_size_t res = strlen(str);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strchr_1) {
  const char *str = "bbaaaa";
  int c = 'a';
  char *s21_res = s21_strchr(str, c);
  char *res = strchr(str, c);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strstr_1) {
  const char *s21_haystack = "abcdef";
  const char *haystack = "abcdef";
  const char *needle = "bcd";
  char *s21_res = s21_strstr(s21_haystack, needle);
  char *res = strstr(haystack, needle);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strtok_n1) {
  char str_s21[] = "hello hello";
  char delim_s21[] = " ";
  char *token_s21 = (s21_strtok(str_s21, delim_s21));

  char str_orig[] = "hello hello";
  char delim_orig[] = " ";
  char *token_orig = (strtok(str_orig, delim_orig));

  while (token_s21 != S21_NULL) {
    ck_assert_str_eq(token_s21, token_orig);
    token_s21 = s21_strtok(S21_NULL, delim_s21);
    token_orig = strtok(S21_NULL, delim_orig);
  }
}
END_TEST

START_TEST(s21_strtok_n2) {
  char str_s21[] = "hello|hello hello";
  char delim_s21[] = "| ";
  char *token_s21 = (s21_strtok(str_s21, delim_s21));

  char str_orig[] = "hello|hello hello";
  char delim_orig[] = "| ";
  char *token_orig = (strtok(str_orig, delim_orig));

  while (token_s21 != S21_NULL) {
    ck_assert_str_eq(token_s21, token_orig);
    token_s21 = s21_strtok(S21_NULL, delim_s21);
    token_orig = strtok(S21_NULL, delim_orig);
  }
}
END_TEST

START_TEST(s21_strtok_n3) {
  char str_s21[] = " A ";
  char delim_s21[] = "A";
  char *token_s21 = (s21_strtok(str_s21, delim_s21));

  char str_orig[] = " A ";
  char delim_orig[] = "A";
  char *token_orig = (strtok(str_orig, delim_orig));

  while (token_s21 != S21_NULL) {
    ck_assert_str_eq(token_s21, token_orig);
    token_s21 = s21_strtok(S21_NULL, delim_s21);
    token_orig = strtok(S21_NULL, delim_orig);
  }
}
END_TEST

START_TEST(s21_strtok_n4) {
  char str_s21[] = " ";
  char delim_s21[] = "";
  char *token_s21 = (s21_strtok(str_s21, delim_s21));

  char str_orig[] = " ";
  char delim_orig[] = "";
  char *token_orig = (strtok(str_orig, delim_orig));

  while (token_s21 != S21_NULL) {
    ck_assert_str_eq(token_s21, token_orig);
    token_s21 = s21_strtok(S21_NULL, delim_s21);
    token_orig = strtok(S21_NULL, delim_orig);
  }
}
END_TEST

// C#

START_TEST(s21_to_upper_n1) {
  const char *s21_str = "upper";

  char *s21_res = s21_to_upper(s21_str);
  char *res = "UPPER";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_upper_n2) {
  const char *s21_str = "upper_casE";

  char *s21_res = s21_to_upper(s21_str);
  char *res = "UPPER_CASE";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_upper_n3) {
  const char *s21_str = "";

  char *s21_res = s21_to_upper(s21_str);
  ck_assert_ptr_null(s21_res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_upper_n4) {
  const char *s21_str = "a|a";

  char *s21_res = s21_to_upper(s21_str);
  char *res = "A|A";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_lower_n1) {
  const char *s21_str = "LOWER";

  char *s21_res = s21_to_lower(s21_str);
  char *res = "lower";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_lower_n2) {
  const char *s21_str = "";

  char *s21_res = s21_to_lower(s21_str);
  ck_assert_ptr_null(s21_res);
  free(s21_res);
}
END_TEST

START_TEST(s21_to_lower_n3) {
  const char *s21_str = "A|A";

  char *s21_res = s21_to_lower(s21_str);
  char *res = "a|a";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_insert_n1) {
  const char *s21_str = "GeeksForGeeks";
  const char *insert_str = "GFG";
  char *s21_res = s21_insert(s21_str, insert_str, 5);
  char *res = "GeeksGFGForGeeks";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

START_TEST(s21_trim_n1) {
  const char *s21_str = "hhellohh";
  const char *trim = "h";

  char *s21_res = s21_trim(s21_str, trim);
  char *res = "ello";
  ck_assert_str_eq(s21_res, res);
  free(s21_res);
}
END_TEST

// strerror
START_TEST(s21_strerror_n1) {
  int errno = 0;

  char *s21_res = s21_strerror(errno);
  char *res = strerror(errno);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strerror_n2) {
  int errno = -1;

  char *s21_res = s21_strerror(errno);
  char *res = strerror(errno);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_strerror_n3) {
  int errno = 134;

  char *s21_res = s21_strerror(errno);
  char *res = strerror(errno);
  ck_assert_str_eq(s21_res, res);
}
END_TEST

// sscanf tests

START_TEST(s21_sscanf_d1) {
  int s21_res, res;
  char *s21_arr = "21";
  char *arr = "21";

  s21_sscanf(s21_arr, "%d", &s21_res);
  sscanf(arr, "%d", &res);
  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_d2) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "21 42";
  char *arr = "21 42";

  s21_sscanf(s21_arr, "%d%d", &s21_res_1, &s21_res_2);
  sscanf(arr, "%d%d", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_d3) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = " 21 42";
  char *arr = " 21 42";

  s21_sscanf(s21_arr, "%d%d", &s21_res_1, &s21_res_2);
  sscanf(arr, "%d%d", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_d4) {
  int s21_res_1, res_1;
  char *s21_arr = "21";
  char *arr = "21";

  s21_sscanf(s21_arr, "%2d", &s21_res_1);
  sscanf(arr, "%2d", &res_1);

  ck_assert_int_eq(s21_res_1, res_1);
}
END_TEST

START_TEST(s21_sscanf_d5) {
  int s21_res_1, res_1;
  char *s21_arr = "+21";
  char *arr = "+21";

  s21_sscanf(s21_arr, "%2d", &s21_res_1);
  sscanf(arr, "%2d", &res_1);

  ck_assert_int_eq(s21_res_1, res_1);
}
END_TEST

START_TEST(s21_sscanf_d6) {
  int s21_res_1, res_1;
  char *s21_arr = "+21";
  char *arr = "+21";

  s21_sscanf(s21_arr, "%d", &s21_res_1);
  sscanf(arr, "%d", &res_1);

  ck_assert_int_eq(s21_res_1, res_1);
}
END_TEST

START_TEST(s21_sscanf_d7) {
  int s21_res_1, res_1;
  char *s21_arr = "-21";
  char *arr = "-21";

  s21_sscanf(s21_arr, "%d", &s21_res_1);
  sscanf(arr, "%d", &res_1);

  ck_assert_int_eq(s21_res_1, res_1);
}
END_TEST

START_TEST(s21_sscanf_d11) {
  int res_d = 0, s21_res_d = 0, num = 0, s21_num = 0; 
  int res_hd = 0, s21_res_hd = 0, res_hhd = 0, s21_res_hhd = 0;
  int res_ld, s21_res_ld;
  long int res_lld, s21_res_lld;

  char *string = "21 21 21 21 0";
  char *format = "%d %d %hd %d %ld %n";

  s21_sscanf(string, format, &s21_res_d, &s21_res_hd, &s21_res_hhd, &s21_res_ld, &s21_res_lld, &s21_num);
  sscanf(string, format, &res_d, &res_hd, &res_hhd, &res_ld, &res_lld, &num);

  ck_assert_int_eq(s21_res_d, res_d);
  ck_assert_int_eq(s21_res_hd, res_hd);
  ck_assert_int_eq(s21_res_hhd, res_hhd);
  ck_assert_int_eq(s21_res_ld, res_ld);
  ck_assert_int_eq(s21_res_lld, res_lld);
  ck_assert_int_eq(s21_num, num);
}

START_TEST(s21_sscanf_d12) {
  int res_d = 0, s21_res_d = 0, num = 0, s21_num = 0; 
  int res_hd = 0, s21_res_hd = 0;
  short int  res_hhd = 0, s21_res_hhd = 0;
  long int res_ld = 0, s21_res_ld = 0;
  long  int res_lld = 0, s21_res_lld = 0;

  char *string = "-21 -21 -21 -12 -12";
  char *format = "%d %d %hd %ld %ld %n";

  s21_sscanf(string, format, &s21_res_d, &s21_res_hd, &s21_res_hhd, &s21_res_ld, &s21_res_lld, &s21_num);
  sscanf(string, format, &res_d, &res_hd, &res_hhd, &res_ld, &res_lld, &num);

  ck_assert_int_eq(s21_res_d, res_d);
  ck_assert_int_eq(s21_res_hd, res_hd);
  ck_assert_int_eq(s21_res_hhd, res_hhd);
  ck_assert_int_eq(s21_res_ld, res_ld);
  ck_assert_int_eq(s21_res_lld, res_lld);
  ck_assert_int_eq(s21_num, num);
}

START_TEST(s21_sscanf_d14) {
  int res_d = 0, s21_res_d = 0, num = 0, s21_num = 0; 
  int res_hd = 0, s21_res_hd = 0;
  int res_hhd = 0, s21_res_hhd = 0;
  long int res_ld = 0, s21_res_ld = 0;
  long int res_lld = 0, s21_res_lld = 0;

  char *string = "21 21 21 12345 1234";
  char *format = "%d %hd %hd %ld %ld %n %";

  s21_sscanf(string, format, &s21_res_d, &s21_res_hd, &s21_res_hhd, &s21_res_ld, &s21_res_lld, &s21_num);
  sscanf(string, format, &res_d, &res_hd, &res_hhd, &res_ld, &res_lld, &num);

  ck_assert_int_eq(s21_res_d, res_d);
  ck_assert_int_eq(s21_res_hd, res_hd);
  ck_assert_int_eq(s21_res_hhd, res_hhd);
  ck_assert_int_eq(s21_res_ld, res_ld);
  ck_assert_int_eq(s21_res_lld, res_lld);
  ck_assert_int_eq(s21_num, num);
}

START_TEST(s21_sscanf_i1) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "-21 42";
  char *arr = "-21 42";

  s21_sscanf(s21_arr, "%i%i", &s21_res_1, &s21_res_2);
  sscanf(arr, "%i%i", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_i2) {
  short int s21_short_res, short_res;
  unsigned short int s21_unsigned_short_res, unsigned_short_res;

  char *s21_arr = "0123 0x212AA";

  s21_sscanf(s21_arr, "%hi %hi %*d", &s21_short_res, &s21_unsigned_short_res);
  sscanf(s21_arr, "%hi %hi %*d", &short_res, &unsigned_short_res);

  ck_assert_int_eq(s21_short_res, short_res);
  ck_assert_int_eq(s21_unsigned_short_res, unsigned_short_res);
}
END_TEST

START_TEST(s21_sscanf_i3) {
  int num, s21_num, res_i, s21_res_i;
  short int res_hi, s21_res_hi;
  short int res_hhi, s21_res_hhi;
  long int res_li, s21_res_li;
  long long int res_lli, s21_res_lli;

  char * string = "1000000 1000000 1000000 1000000 1000000";
  char * format = "%1i %2hi %3hi %4li %4li %n";

  s21_sscanf(string, format, &s21_res_i, &s21_res_hi, &s21_res_hhi, &s21_res_li, &s21_res_lli, &s21_num);
  sscanf(string, format, &res_i, &res_hi, &res_hhi, &res_li, &res_lli, &num);

  ck_assert_int_eq(res_i, s21_res_i);
  ck_assert_int_eq(res_hi, s21_res_hi);
  ck_assert_int_eq(res_hhi, s21_res_hhi);
  ck_assert_int_eq(res_li, s21_res_li);
  ck_assert_int_eq(res_lli, s21_res_lli);
  ck_assert_int_eq(num, s21_num);
}

START_TEST(s21_sscanf_i4) {
  int num = 0, s21_num = 0, res_i = 0, s21_res_i = 0;
  unsigned int res_hi = 0, s21_res_hi = 0;
  int res_hhi = 0, s21_res_hhi = 0;
  long int res_li = 0, s21_res_li = 0;
  long  int res_lli = 0, s21_res_lli = 0;

  char * string = "-100 -1 -1 -1000000 -1000000";
  char * format = "%i %0i %i %4li %4li %n";

  s21_sscanf(string, format, &s21_res_i, &s21_res_hi, &s21_res_hhi, &s21_res_li, &s21_res_lli, &s21_num);
  sscanf(string, format, &res_i, &res_hi, &res_hhi, &res_li, &res_lli, &num);

  ck_assert_int_eq(res_i, s21_res_i);
  ck_assert_int_eq(res_hi, s21_res_hi);
  ck_assert_int_eq(res_hhi, s21_res_hhi);
  ck_assert_int_eq(res_li, s21_res_li);
  ck_assert_int_eq(res_lli, s21_res_lli);
  ck_assert_int_eq(num, s21_num);
}

START_TEST(s21_sscanf_i5) {
  int num, s21_num, res_i, s21_res_i;
  int res_hi, s21_res_hi;
  short int res_hhi, s21_res_hhi;
  long int res_li, s21_res_li;
  long long int res_lli, s21_res_lli;

  char * string = "1 -1000000 -1 -1 -1000000";
  char * format = "%i %i %i %li %li %n";

  s21_sscanf(string, format, &s21_res_i, &s21_res_hi, &s21_res_hhi, &s21_res_li, &s21_res_lli, &s21_num);
  sscanf(string, format, &res_i, &res_hi, &res_hhi, &res_li, &res_lli, &num);

  ck_assert_int_eq(res_i, s21_res_i);
  ck_assert_int_eq(res_hi, s21_res_hi);
  ck_assert_int_eq(res_hhi, s21_res_hhi);
  ck_assert_int_eq(res_li, s21_res_li);
  ck_assert_int_eq(res_lli, s21_res_lli);
  ck_assert_int_eq(num, s21_num);
}


START_TEST(s21_sscanf_f1) {
  float s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "-21.21 42.42";
  char *arr = "-21.21 42.42";

  s21_sscanf(s21_arr, "%f%f", &s21_res_1, &s21_res_2);
  sscanf(arr, "%f%f", &res_1, &res_2);

  ck_assert_float_eq(s21_res_1, res_1);
  ck_assert_float_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_f2) {
  float s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "+21.21 +42.42";
  char *arr = "+21.21 +42.42";

  s21_sscanf(s21_arr, "%f%f", &s21_res_1, &s21_res_2);
  sscanf(arr, "%f%f", &res_1, &res_2);

  ck_assert_float_eq(s21_res_1, res_1);
  ck_assert_float_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_u1) {
  unsigned int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "21 42";
  char *arr = "21 42";

  s21_sscanf(s21_arr, "%u%u", &s21_res_1, &s21_res_2);
  sscanf(arr, "%u%u", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_u2) {
  unsigned int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "0 255";
  char *arr = "0 255";

  s21_sscanf(s21_arr, "%u%u", &s21_res_1, &s21_res_2);
  sscanf(arr, "%u%u", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_u3) {
  unsigned int s21_res_1, res_1;
  char *s21_arr = "     21";
  char *arr = "     21";

  s21_sscanf(s21_arr, "%u", &s21_res_1);
  sscanf(arr, "%u", &res_1);

  ck_assert_uint_eq(s21_res_1, res_1);
  // ck_assert_int_eq(s21_res_1, res_1);
}
END_TEST

START_TEST(s21_sscanf_o1) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *s21_arr = "0 377";
  char *arr = "0 377";

  s21_sscanf(s21_arr, "%o%o", &s21_res_1, &s21_res_2);
  sscanf(arr, "%o%o", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_o2) {
  int s21_res, res;
  char *s21_arr = "015";

  s21_sscanf(s21_arr, "%o", &s21_res);
  sscanf(s21_arr, "%o", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_o3) {
  int s21_res, res;
  char *s21_arr = "-015";

  s21_sscanf(s21_arr, "%o", &s21_res);
  sscanf(s21_arr, "%o", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_o4) {
  int s21_res, res;
  char *s21_arr = "0-15";

  s21_sscanf(s21_arr, "%o", &s21_res);
  sscanf(s21_arr, "%o", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_x1) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *arr = "0 255";

  s21_sscanf(arr, "%x %x", &s21_res_1, &s21_res_2);
  sscanf(arr, "%x %x", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_x2) {
  int s21_res_1, s21_res_2, res_1, res_2;
  char *arr = "0x15 0x2A";

  s21_sscanf(arr, "%x %x", &s21_res_1, &s21_res_2);
  sscanf(arr, "%x %x", &res_1, &res_2);

  ck_assert_int_eq(s21_res_1, res_1);
  ck_assert_int_eq(s21_res_2, res_2);
}
END_TEST

START_TEST(s21_sscanf_x3) {
  int s21_res, res;
  char *arr = "0x15";

  s21_sscanf(arr, "%x", &s21_res);
  sscanf(arr, "%x", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_n1) {
  int res_n = 0, s21_res_n = 0, num = 0, s21_num = 0;
  char *arr = " 21 school ";

  char string_res[200] = "", s21_string_res[200] = "";

  s21_sscanf(arr, "%d %s %n", &s21_num, s21_string_res, &s21_res_n);
  sscanf(arr, "%d %s %n", &num, string_res, &res_n);

  ck_assert_int_eq(s21_num, num);
  ck_assert_str_eq(s21_string_res, string_res);
  ck_assert_int_eq(s21_res_n, res_n);
}
END_TEST

START_TEST(s21_sscanf_n2) {
  int res_n = 0, s21_res_n = 0, num = 0, s21_num = 0;
  char *arr = " 21s ";

  char string_res[20] = "", s21_string_res[20] = "";

  s21_sscanf(arr, "%d %s %n", &s21_num, s21_string_res, &s21_res_n);
  sscanf(arr, "%d %s %n", &num, string_res, &res_n);

  ck_assert_int_eq(s21_num, num);
  ck_assert_str_eq(s21_string_res, string_res);
  ck_assert_int_eq(s21_res_n, res_n);
}
END_TEST

START_TEST(s21_sscanf_n3) {
  int res_n, s21_res_n;
  char arr[1] = " * ";

  char string_res[20] = "", s21_string_res[20] = "";

  s21_sscanf("1234 03332 ", "%s %n", s21_string_res, &s21_res_n);
  sscanf("1234 03332 ", "%s %n", string_res, &res_n);


  ck_assert_str_eq(string_res, s21_string_res);
  ck_assert_int_eq(s21_res_n, res_n);
}
END_TEST

START_TEST(s21_sscanf_n4) {
  int res_n = 0, s21_res_n = 0;


  char string_res[20] = "", s21_string_res[20] = "";

  s21_sscanf("1234", "%1s%n", s21_string_res, &s21_res_n);
  sscanf("1234", "%1s%n", string_res, &res_n);

  ck_assert_str_eq(s21_string_res, string_res);
  ck_assert_int_eq(s21_res_n, res_n);
}
END_TEST

START_TEST(s21_sscanf_n5) {
  int res_n, s21_res_n;

  char string_res[20] = "", s21_string_res[20] = "";

  s21_sscanf(" a ", "%s %n", s21_string_res, &s21_res_n);
  sscanf(" a ", "%s %n", string_res, &res_n);

  ck_assert_str_eq(s21_string_res, string_res);
  ck_assert_int_eq(s21_res_n, res_n);
}
END_TEST

START_TEST(s21_sscanf_p2) {
  int num = 21;
  char ptr_arr[21] = "";
  char *res = NULL, *s21_res = NULL;

  sprintf(ptr_arr, "%p", &num);
  s21_sscanf("0x12345678 0x12345678", "%*p %p", (void **)&s21_res);
  sscanf("0x12345678 0x12345678", "%*p %p", (void **)&res);

  ck_assert_ptr_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c1) {
  char *c = "c";
  char res, s21_res;

  s21_sscanf(c, "%c", &s21_res);
  sscanf(c, "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c2) {
  char res, s21_res;

  s21_sscanf("a", "%c", &s21_res);
  sscanf("a", "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c3) {
  char *c = " ";
  char res, s21_res;

  s21_sscanf(c, "%c", &s21_res);
  sscanf(c, "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c4) {
  char *c = "_";
  char res, s21_res;

  s21_sscanf(c, "%c", &s21_res);
  sscanf(c, "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c5) {
  char *c = "%%";
  char res, s21_res;

  s21_sscanf(c, "%c", &s21_res);
  sscanf(c, "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_c6) {
  char *c = "\\%%";
  char res, s21_res;

  s21_sscanf(c, "%c", &s21_res);
  sscanf(c, "%c", &res);

  ck_assert_int_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e1) {
  double res = 0, s21_res = 0;

  s21_sscanf("0", "%le", &s21_res);
  sscanf("0", "%le", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e2) {
  long double res = 0, s21_res = 0;

  s21_sscanf("12345E+06", "%lE", &s21_res);
  sscanf("12345E+06", "%lE", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e3) {
  long double res = 0, s21_res = 0;

  s21_sscanf("-1e+1", "%le", &s21_res);
  sscanf("-1e+1", "%le", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e4) {
  long double res = 0;
  long double s21_res = 0;

  s21_sscanf("1e1", "%lE", &s21_res);
  sscanf("1e1", "%lE", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e5) {
  long double res = 0, s21_res = 0;

  s21_sscanf("12345", "%lE", &s21_res);
  sscanf("12345", "%lE", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e6) {
   long double res = 0, s21_res = 0;

  s21_sscanf("12345", "%le", &s21_res);
  sscanf("12345", "%le", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_e7) {
  long double res = 0, s21_res = 0;

  s21_sscanf("12345eE+06", "%le", &s21_res);
  sscanf("12345eE+06", "%le", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g1) {
  char *notation = "12345.6789";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lg", &s21_res);
  sscanf(notation, "%lg", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g2) {
  char *notation = "12345.6789";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lG", &s21_res);
  sscanf(notation, "%lG", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g3) {
  char *notation = "123e+04";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lg", &s21_res);
  sscanf(notation, "%lg", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g4) {
  char *notation = "123E+04";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lG", &s21_res);
  sscanf(notation, "%lG", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g5) {
  char *notation = "-12345.6789";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lg", &s21_res);
  sscanf(notation, "%lg", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g6) {
  char *notation = "-12345.6789";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lG", &s21_res);
  sscanf(notation, "%lG", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g7) {
  char *notation = "-123e+04";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lg", &s21_res);
  sscanf(notation, "%lg", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g8) {
  char *notation = "-123E+04";
  long double res = 0, s21_res = 0;

  s21_sscanf(notation, "%lG", &s21_res);
  sscanf(notation, "%lG", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g9) {
  char *notation = "-12345";
  long double s21_res = 0;
  long double res = 0;

  s21_sscanf("-12345", "%lg", &s21_res);
  sscanf("-12345", "%lg", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_g10) {
  char *notation = "-12345";
  long double s21_res = 0;
  long double res = 0;

  s21_sscanf("-12345", "%lG", &s21_res);
  sscanf("-12345", "%lG", &res);

  ck_assert_double_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_l1) {  // жестб
  char *notation = "1234567890 1.234567890";
  long long_res, s21_long_res;
  long double long_double_res, s21_long_double_res;

  s21_sscanf(notation, "%ld %Lf", &s21_long_res, &s21_long_double_res);
  sscanf(notation, "%ld %Lf", &long_res, &long_double_res);

  ck_assert_int_eq(s21_long_res, long_res);
  ck_assert_double_eq_tol(s21_long_double_res, long_double_res, 1e-15);
}
END_TEST

START_TEST(s21_sscanf_l2) {
  char *notation = "-1234567890 -1.234567890";
  long long_res, s21_long_res;
  long double long_double_res, s21_long_double_res;

  s21_sscanf(notation, "%ld %Lf", &s21_long_res, &s21_long_double_res);
  sscanf(notation, "%ld %Lf", &long_res, &long_double_res);

  ck_assert_int_eq(s21_long_res, long_res);
  ck_assert_double_eq_tol(s21_long_double_res, long_double_res, 1e-15);
}
END_TEST

START_TEST(s21_sscanf_s1) {
  char *string = "school 21";
  char res[1024], s21_res[1024];

  s21_sscanf(string, "%s", s21_res);
  sscanf(string, "%s", res);

  ck_assert_str_eq(s21_res, res);
}
END_TEST

START_TEST(s21_sscanf_s2) {
  char *string = "            school 21";
  char res[1024], s21_res[1024];

  s21_sscanf(string, "%s", s21_res);
  sscanf(string, "%s", res);

  ck_assert_str_eq(s21_res, res);
}
END_TEST

// Alyona

START_TEST(s21_sscanf_alyona_g_1) {
  char *string = "0 0 0 0 0.0 0";
  char *format = "%g %G %e %E %f %*g";

  float res_g = 0, s21_res_g = 0, res_big_g = 0, s21_res_big_g = 0, res_e = 0, s21_res_e = 0, res_big_e = 0, s21_res_big_e = 0, res_f = 0, s21_res_f = 0, res_star_g = 0, s21_res_star_g = 0;


  s21_sscanf(string, format, &s21_res_g, &s21_res_big_g, &s21_res_e, &s21_res_big_e, &s21_res_f, &s21_res_star_g);
  sscanf(string, format, &res_g, &res_big_g, &res_e, &res_big_e, &res_f, &res_star_g);

  ck_assert_float_eq(res_g, s21_res_g);
  ck_assert_float_eq(res_big_g, s21_res_big_g);
  ck_assert_float_eq(res_e, s21_res_e);
  ck_assert_float_eq(res_big_e, s21_res_big_e);
  ck_assert_float_eq(res_f, s21_res_f);
  ck_assert_float_eq(res_star_g, s21_res_star_g);
}
END_TEST

START_TEST(s21_sscanf_alyona_i_1) {
  int res_1 = 0, res_2 = 0, s21_res_1 = 0, s21_res_2 = 0;

  char *string = "0x7ffc12345678 0x7ffc12345678";
  char *format = "%*i %i";

  s21_sscanf(string, format, &s21_res_1, &s21_res_2);
  sscanf(string, format, &res_1, &res_2);

  ck_assert_int_eq(res_1, s21_res_1);
  ck_assert_int_eq(res_2, s21_res_2);
}
END_TEST

START_TEST(s21_sscanf_alyona_i_2) {
  int res_1 = 0, res_2 = 0, s21_res_1 = 0, s21_res_2 = 0;

  char *string = "0x7ffc12345678 07ffc12345678";
  char *format = "%*i %i";

  s21_sscanf(string, format, &s21_res_1, &s21_res_2);
  sscanf(string, format, &res_1, &res_2);

  ck_assert_int_eq(res_1, s21_res_1);
  ck_assert_int_eq(res_2, s21_res_2);
}
END_TEST

START_TEST(s21_sscanf_alyona_i_3) {
  int res_1 = 0, s21_res_1 = 0;

  char *string = "0x7ffc12345678 07ffc12345678";
  char *format = "%*i %";

  s21_sscanf(string, format, &s21_res_1);
  sscanf(string, format, &res_1);

  ck_assert_int_eq(res_1, s21_res_1);
}
END_TEST

START_TEST(s21_sscanf_alyona_i_4) {
  int res_1 = 0, s21_res_1 = 0;

  char *string = "0x7ffc12345678 07ffc12345678";
  char *format = "% %%  ";

  s21_sscanf(string, format, &s21_res_1);
  sscanf(string, format, &res_1);

  ck_assert_int_eq(res_1, s21_res_1);
}
END_TEST

START_TEST(s21_sscanf_alyona_i_5) {
  int res = 0, s21_res = 0;
  char * string = "0x7ffc12345678 07ffc12345678";
  char *format = "%*i %";
  s21_sscanf(string, format, &s21_res);
  sscanf(string, format, &res);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(s21_sscanf_alyona_d_1) {
  int res, s21_res;
  char * string = "5";
  char *format = "%d % ";
  s21_sscanf(string, format, &s21_res);
  sscanf(string, format, &res);

  ck_assert_int_eq(res, s21_res);
}
END_TEST

START_TEST(s21_sscanf_alyona_minuses_1) {
  unsigned long int s21_uli_u, std_uli_u, s21_uli_x, std_uli_x, s21_uli_X, std_uli_X,
   s21_uli_o, std_uli_o;
  long int s21_li_d, std_li_d, s21_li_i, std_li_i;

  char * string = "-1 -1 -1 -1 -1 -1";
  char *format = "%ld %lo %lx %lX %lu %li";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);
}
END_TEST

START_TEST(s21_sscanf_alyona_minuses_2) {
  unsigned long int s21_uli_u, std_uli_u, s21_uli_x, std_uli_x, s21_uli_X, std_uli_X,
   s21_uli_o, std_uli_o;
  long int s21_li_d, std_li_d, s21_li_i, std_li_i;
  double s21_mg = 0, std_mg = 0, s21_me = 0, std_me = 0;

  char * string = "-1 -1 -1 -1 -1 -1 -1 -1";
  char *format = "%ld %lo %lx %lX %lu %li %e";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i, &s21_me, &s21_mg);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i, &std_me, &std_mg);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);

    ck_assert_double_eq(s21_mg, std_mg);
    ck_assert_double_eq(s21_me, std_me);
}
END_TEST

START_TEST(s21_sscanf_alyona_minuses_long_double) {
  unsigned long int s21_uli_u = 0, std_uli_u = 0, s21_uli_x = 0, std_uli_x = 0, s21_uli_X = 0, std_uli_X = 0,
   s21_uli_o = 0, std_uli_o =0;
  long int s21_li_d = 0, std_li_d = 0, s21_li_i = 0, std_li_i = 0;
  long double s21_mg = 0, std_mg = 0, s21_me = 0, std_me = 0;

  char * string = "-1 -1 -1 -1 -1 -1 -1 -1";
  char *format = "%ld %lo %lx %lX %lu %li %Le %g";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i, &s21_me, &s21_mg);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i, &std_me, &std_mg);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);

    ck_assert_double_eq(s21_mg, std_mg);
    ck_assert_double_eq(s21_me, std_me);
}
END_TEST

START_TEST(s21_sscanf_alyona_minuses_3) {
  long int s21_uli_u = 0, std_uli_u = 0, s21_uli_x = 0, std_uli_x = 0, s21_uli_X = 0, std_uli_X = 0,
   s21_uli_o, std_uli_o;
  long int s21_li_d = 0, std_li_d = 0, s21_li_i = 0, std_li_i = 0;
  double s21_mg = 0, std_mg = 0, s21_me = 0, std_me = 0;

  char * string = "-1 -1 -1 -1 -1 -1 -1 -1";
  char *format = "%ld %lo %lx %lX %lu %li %e %g";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i, &s21_me, &s21_mg);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i, &std_me, &std_mg);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);

    ck_assert_double_eq(s21_mg, std_mg);
    ck_assert_double_eq(s21_me, std_me);
}
END_TEST

START_TEST(s21_sscanf_alyona_minuses_2_zero) {
  unsigned long int s21_uli_u = 0, std_uli_u = 0, s21_uli_x = 0, std_uli_x = 0, s21_uli_X = 0, std_uli_X = 0,
   s21_uli_o = 0, std_uli_o = 0;
  long int s21_li_d = 0, std_li_d = 0, s21_li_i = 0, std_li_i = 0;
  double s21_mg = 0, std_mg = 0, s21_me = 0, std_me = 0;

  char * string = "-1 -1 -1 -1 -1 -1 -1 -1";
  char *format = "%ld %lo %lx %lX %lu %li %e %g";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i, &s21_me, &s21_mg);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i, &std_me, &std_mg);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);

    ck_assert_double_eq(s21_mg, std_mg);
    ck_assert_double_eq(s21_me, std_me);
}
END_TEST

START_TEST(s21_sscanf_alyona_non_minuses_1) {
  unsigned long int s21_uli_u = 0, std_uli_u = 0, s21_uli_x = 0, std_uli_x = 0, s21_uli_X = 0, std_uli_X = 0,
   s21_uli_o = 0 , std_uli_o = 0;
  long int s21_li_d = 0, std_li_d = 0, s21_li_i = 0, std_li_i = 0;
  double s21_mg = 0, std_mg = 0, s21_me = 0, std_me = 0;

  char * string = "1 1 1 1 1 1 1 1";
  char *format = "%ld %lo %lx %lX %lu %li %e %g";

  s21_sscanf(string, format, &s21_li_d, &s21_uli_o,
    &s21_uli_x, &s21_uli_X, &s21_uli_u, &s21_li_i, &s21_me, &s21_mg);
  sscanf(string, format, &std_li_d, &std_uli_o,
    &std_uli_x, &std_uli_X, &std_uli_u, &std_li_i, &std_me, &std_mg);

    ck_assert_int_eq(s21_uli_u, std_uli_u);
    ck_assert_int_eq(s21_uli_x, std_uli_x);
    ck_assert_int_eq(s21_uli_X, std_uli_X);
    ck_assert_int_eq(s21_uli_o, std_uli_o);
    ck_assert_int_eq(s21_li_d, std_li_d);
    ck_assert_int_eq(s21_li_i, std_li_i);

    ck_assert_double_eq(s21_mg, std_mg);
    ck_assert_double_eq(s21_me, std_me);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, s21_strncat_1);
  tcase_add_test(tc1_1, s21_strncat_2);
  tcase_add_test(tc1_1, s21_memchr_1);
  tcase_add_test(tc1_1, s21_memchr_2);
  tcase_add_test(tc1_1, s21_memchr_3);
  tcase_add_test(tc1_1, s21_memcmp_1);
  tcase_add_test(tc1_1, s21_memcmp_2);
  tcase_add_test(tc1_1, s21_memcmp_3);
  tcase_add_test(tc1_1, s21_memcmp_4);
  tcase_add_test(tc1_1, s21_memcpy_1);
  tcase_add_test(tc1_1, s21_memcpy_2);
  tcase_add_test(tc1_1, s21_memcpy_3);
  tcase_add_test(tc1_1, s21_memset_1);
  tcase_add_test(tc1_1, s21_memset_2);
  tcase_add_test(tc1_1, s21_strstr_1);
  tcase_add_test(tc1_1, s21_strchr_1);
  tcase_add_test(tc1_1, s21_strlen_1);
  tcase_add_test(tc1_1, s21_strpbrk_1);
  tcase_add_test(tc1_1, s21_strcspn_1);
  tcase_add_test(tc1_1, s21_strrchr_1);

  // tcase_add_test(tc1_1, s21_strncat_1);
  // SPRINTF
  tcase_add_test(tc1_1, s21_sprintf_d1);
  tcase_add_test(tc1_1, s21_sprintf_d2);
  tcase_add_test(tc1_1, s21_sprintf_d3);
  tcase_add_test(tc1_1, s21_sprintf_d4);
  tcase_add_test(tc1_1, s21_sprintf_d5);
  tcase_add_test(tc1_1, s21_sprintf_f1);
  tcase_add_test(tc1_1, s21_sprintf_f2);
  tcase_add_test(tc1_1, s21_sprintf_f3);
  tcase_add_test(tc1_1, s21_sprintf_u1);
  tcase_add_test(tc1_1, s21_sprintf_u2);
  tcase_add_test(tc1_1, s21_sprintf_x1);
  tcase_add_test(tc1_1, s21_sprintf_x2);
  tcase_add_test(tc1_1, s21_sprintf_x3);
  tcase_add_test(tc1_1, s21_sprintf_i1);
  tcase_add_test(tc1_1, s21_sprintf_e1);
  tcase_add_test(tc1_1, s21_sprintf_e2);
  tcase_add_test(tc1_1, s21_sprintf_g1);
  tcase_add_test(tc1_1, s21_sprintf_o1);
  tcase_add_test(tc1_1, s21_sprintf_s1);
  tcase_add_test(tc1_1, s21_sprintf_p1);
  tcase_add_test(tc1_1, s21_sprintf_c1);
  tcase_add_test(tc1_1, s21_sprintf_c2);
  tcase_add_test(tc1_1, s21_sprintf_n1);
  tcase_add_test(tc1_1, s21_sprintf_percent);

  tcase_add_test(tc1_1, s21_strtok_n1);
  tcase_add_test(tc1_1, s21_strtok_n2);
  tcase_add_test(tc1_1, s21_strtok_n3);
  tcase_add_test(tc1_1, s21_strtok_n4);

  // C#

  tcase_add_test(tc1_1, s21_to_upper_n1);
  tcase_add_test(tc1_1, s21_to_upper_n2);
  tcase_add_test(tc1_1, s21_to_upper_n3);
  tcase_add_test(tc1_1, s21_to_upper_n4);

  tcase_add_test(tc1_1, s21_to_lower_n1);
  tcase_add_test(tc1_1, s21_to_lower_n2);
  tcase_add_test(tc1_1, s21_to_lower_n3);

  tcase_add_test(tc1_1, s21_insert_n1);
  tcase_add_test(tc1_1, s21_trim_n1);

  // strerror
  tcase_add_test(tc1_1, s21_strerror_n1);
  tcase_add_test(tc1_1, s21_strerror_n2);
  tcase_add_test(tc1_1, s21_strerror_n3);

  // sscanf
  tcase_add_test(tc1_1, s21_sscanf_d1);
  tcase_add_test(tc1_1, s21_sscanf_d2);
  tcase_add_test(tc1_1, s21_sscanf_d3);
  tcase_add_test(tc1_1, s21_sscanf_d4);
  tcase_add_test(tc1_1, s21_sscanf_d5);
  tcase_add_test(tc1_1, s21_sscanf_d6);
  tcase_add_test(tc1_1, s21_sscanf_d7);
  tcase_add_test(tc1_1, s21_sscanf_d11);
  tcase_add_test(tc1_1, s21_sscanf_d12);
  tcase_add_test(tc1_1, s21_sscanf_d14);
  tcase_add_test(tc1_1, s21_sscanf_i1);
  tcase_add_test(tc1_1, s21_sscanf_i2);
  tcase_add_test(tc1_1, s21_sscanf_i3);
  tcase_add_test(tc1_1, s21_sscanf_i4);
  tcase_add_test(tc1_1, s21_sscanf_i5);
  tcase_add_test(tc1_1, s21_sscanf_f1);
  tcase_add_test(tc1_1, s21_sscanf_f2);
  tcase_add_test(tc1_1, s21_sscanf_u1);
  tcase_add_test(tc1_1, s21_sscanf_u2);
  tcase_add_test(tc1_1, s21_sscanf_u3);
  tcase_add_test(tc1_1, s21_sscanf_o1);
  tcase_add_test(tc1_1, s21_sscanf_o2);
  tcase_add_test(tc1_1, s21_sscanf_o3);
  tcase_add_test(tc1_1, s21_sscanf_o4);
  tcase_add_test(tc1_1, s21_sscanf_x1);
  tcase_add_test(tc1_1, s21_sscanf_x2);
  tcase_add_test(tc1_1, s21_sscanf_x3);
  tcase_add_test(tc1_1, s21_sscanf_c1);
  tcase_add_test(tc1_1, s21_sscanf_s1);
  tcase_add_test(tc1_1, s21_sscanf_n1);
  tcase_add_test(tc1_1, s21_sscanf_n2);
  tcase_add_test(tc1_1, s21_sscanf_n3);
  tcase_add_test(tc1_1, s21_sscanf_n4);
  tcase_add_test(tc1_1, s21_sscanf_n5);
  tcase_add_test(tc1_1, s21_sscanf_p2);
  tcase_add_test(tc1_1, s21_sscanf_c1);
  tcase_add_test(tc1_1, s21_sscanf_c2);
  tcase_add_test(tc1_1, s21_sscanf_c3);
  tcase_add_test(tc1_1, s21_sscanf_c4);
  tcase_add_test(tc1_1, s21_sscanf_c5);
  tcase_add_test(tc1_1, s21_sscanf_c6);
  tcase_add_test(tc1_1, s21_sscanf_e1);
  tcase_add_test(tc1_1, s21_sscanf_e2);
  tcase_add_test(tc1_1, s21_sscanf_e3);
  tcase_add_test(tc1_1, s21_sscanf_e4);
  tcase_add_test(tc1_1, s21_sscanf_e5);
  tcase_add_test(tc1_1, s21_sscanf_e6);
  tcase_add_test(tc1_1, s21_sscanf_e7);
  tcase_add_test(tc1_1, s21_sscanf_g1);
  tcase_add_test(tc1_1, s21_sscanf_g2);
  tcase_add_test(tc1_1, s21_sscanf_g3);
  tcase_add_test(tc1_1, s21_sscanf_g4);
  tcase_add_test(tc1_1, s21_sscanf_g5);
  tcase_add_test(tc1_1, s21_sscanf_g6);
  tcase_add_test(tc1_1, s21_sscanf_g7);
  tcase_add_test(tc1_1, s21_sscanf_g8);
  tcase_add_test(tc1_1, s21_sscanf_g9);
  tcase_add_test(tc1_1, s21_sscanf_g10);
  tcase_add_test(tc1_1, s21_sscanf_s1);
  tcase_add_test(tc1_1, s21_sscanf_s2);
  tcase_add_test(tc1_1, s21_sscanf_l1);
  tcase_add_test(tc1_1, s21_sscanf_l2);

  // Alyona
  tcase_add_test(tc1_1, s21_sscanf_alyona_g_1);
  tcase_add_test(tc1_1, s21_sscanf_alyona_i_1);
  tcase_add_test(tc1_1, s21_sscanf_alyona_i_2);
  tcase_add_test(tc1_1, s21_sscanf_alyona_i_3);
  tcase_add_test(tc1_1, s21_sscanf_alyona_i_4);
  tcase_add_test(tc1_1, s21_sscanf_alyona_i_5);
  tcase_add_test(tc1_1, s21_sscanf_alyona_d_1);
  tcase_add_test(tc1_1, s21_sscanf_alyona_minuses_1);
  tcase_add_test(tc1_1, s21_sscanf_alyona_minuses_2);
  tcase_add_test(tc1_1, s21_sscanf_alyona_minuses_3);
  tcase_add_test(tc1_1, s21_sscanf_alyona_minuses_2_zero);
  tcase_add_test(tc1_1, s21_sscanf_alyona_non_minuses_1);
  tcase_add_test(tc1_1, s21_sscanf_alyona_minuses_long_double);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}