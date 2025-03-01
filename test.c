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

// START_TEST(s21_sscanf_read_d1)

// END_TEST

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

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}