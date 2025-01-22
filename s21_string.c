#include "s21_string.h"

int is_negative(long double a) { return 1.0L / a < 0.0L; }

double my_abs(long double a) { return is_negative(a) ? -a : a; }

void reverse_str(char *str) {
  int i = 0, j = s21_strlen(str) - 1, temp;
  while (i < j) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

long long int my_round(long double num) {
  long long int int_part = (long long int)num;
  long double frac_part = num - int_part;

  if (frac_part > 0.5) {
    return int_part + 1;
  } else {
    return int_part;
  }
}

long double round_to_precision(long double value, int precision) {
  long double factor = pow(10.0, precision);
  long double int_part = 0;
  long double frac_part = 0;
  frac_part = my_abs(modfl(value * factor, &int_part));
  int is_neg = is_negative(value);
  int_part = my_abs(int_part);
  long double rez = 0;

  if (frac_part < 0.5) {
    rez = floor(my_abs(value * factor)) / factor;
  } else if (frac_part > 0.5) {
    rez = ceil(my_abs(value * factor)) / factor;
  } else {
    if ((long long)int_part % 2 == 0) {
      rez = int_part / factor;
    } else {
      rez = (int_part + 1) / factor;
    }
  }

  return (is_neg ? -1.0L : 1.0L) * rez;
}

int unsigned_number(char *str, specification_read spec_read, long double num) {
  utos(str, num, spec_read.accuracy);
  return s21_strlen(str);
}

int integer_number(char *str, specification_read spec_read, long double num) {
  itos(str, num, spec_read.accuracy);
  return s21_strlen(str);
}

int octal_number(char *str, specification_read spec_read, long long int num) {
  int index = 0;
  while (num / 8 != 0) {
    str[index++] = num % 8 + '0';
    num /= 8;
  }
  str[index++] = num % 8 + '0';
  if (spec_read.flag_hash) {
    str[index++] = '0';
  }
  reverse_str(str);
  str[index] = '\0';
  return index;
}

int hexidecimal_number(char *str, specification_read spec_read,
                       long long int num, int big) {
  int index = 0;
  while (num / 16 != 0) {
    str[index++] = big ? hexidecimal_big[num % 16] : hexidecimal[num % 16];
    num /= 16;
  }
  str[index++] = big ? hexidecimal_big[num % 16] : hexidecimal[num % 16];
  if (spec_read.flag_hash) {
    str[index++] = big ? 'X' : 'x';
    str[index++] = '0';
  }
  reverse_str(str);
  str[index] = '\0';
  return index;
}

int integer_part_len(long double num) {
  long long int int_part = 0;
  int_part = (long long int)num;
  int counter = 0;
  while (int_part != 0) {
    int_part /= 10;
    counter++;
  }
  return counter;
}

int find_start(long double num) {
  long double int_part;
  long double frac_part = modfl(my_abs(num), &int_part);
  int rez = -1;
  if (frac_part != 0) {
    while ((long long int)frac_part == 0) {
      frac_part = frac_part * 10;
      rez++;
    }
  } else
    rez = 0;
  return rez;
}

int count_significant(int so, int accuracy, long double num, int hash_flag) {
  long double int_part;
  long double frac_part = modfl(my_abs(num), &int_part);
  int counter = 0;
  while ((long long int)int_part != 0) {
    int_part /= 10;
    accuracy--;
  }

  frac_part *= pow(10, so);
  frac_part = round_to_precision(frac_part, accuracy);
  frac_part *= pow(10, accuracy);

  while (((long long int)frac_part % (long long int)pow(10, accuracy) != 0 ||
          hash_flag) &&
         accuracy > 0) {
    counter++;
    accuracy--;
  }

  return counter;
}

int float_number(char *str, specification_read spec_read, long double num) {
  num = round_to_precision(num, spec_read.accuracy);
  ftos(str, num, spec_read.accuracy,
       spec_read.accuracy > 0 || spec_read.flag_hash);
  return s21_strlen(str);
}

long double prepare_science(long double num, int *e) {
  *e = 0;
  if (num == 0.0) {
    *e = 0;
  } else if ((long long int)num == 0) {
    while (my_abs(num) < 1) {
      num *= 10;
      *e -= 1;
    }
  } else {
    while (my_abs(num) >= 10) {
      num /= 10;
      *e += 1;
    }
  }
  return num;
}

int etos(char *str, specification_read spec_read, long double num, int e) {
  num = round_to_precision(num, spec_read.accuracy);
  ftos(str, num, spec_read.accuracy,
       spec_read.accuracy > 0 || spec_read.flag_hash);
  s21_size_t num_len = s21_strlen(str);
  char *ptr = str + num_len;
  *(ptr++) = spec_read.spec;
  *(ptr++) = e < 0 ? '-' : '+';
  itos(ptr, my_abs(e), 2);

  return num_len + 2 + s21_strlen(ptr);
}

int science_number(char *str, specification_read spec_read, long double num) {
  int e;
  num = prepare_science(num, &e);
  return etos(str, spec_read, num, e);
}

int digit_specificator(char *str, specification_read spec_read,
                       long double num) {
  char *ptr = str;
  char num_str[124] = {0};
  int num_len = 0;
  if (spec_read.spec == 'f') {
    num_len = float_number(num_str, spec_read, num);
  } else if (spec_read.spec == 'e' || spec_read.spec == 'E') {
    num_len = science_number(num_str, spec_read, num);
  } else if (spec_read.spec == 'g' || spec_read.spec == 'G') {
    spec_read.spec = spec_read.spec + 'e' - 'g';
    int int_len = integer_part_len(num);
    int is_e = int_len > spec_read.accuracy || my_abs(num) < 0.0001 ||
               my_abs(num) > 999999;
    int e;
    if (is_e) num = prepare_science(num, &e);
    int so = find_start(num);
    int need_accuracy =
        count_significant(so, spec_read.accuracy, num, spec_read.flag_hash);
    spec_read.accuracy = so + need_accuracy;
    if (is_e)
      num_len = etos(num_str, spec_read, num, e);
    else
      num_len = float_number(num_str, spec_read, num);
  } else if (spec_read.spec == 'o')
    num_len = octal_number(num_str, spec_read, num);
  else if (spec_read.spec == 'x' || spec_read.spec == 'X')
    num_len =
        hexidecimal_number(num_str, spec_read, num, spec_read.spec == 'X');
  else if (spec_read.spec == 'u')
    num_len = unsigned_number(num_str, spec_read, num);
  else
    num_len = integer_number(num_str, spec_read, num);

  char space = 0;
  if (spec_read.flag_minus) spec_read.flag_zero = 0;
  if (spec_read.spec != 'u' && spec_read.spec != 'o' && spec_read.spec != 'x' &&
      spec_read.spec != 'X') {
    if (is_negative(num))
      space = '-';
    else if (spec_read.flag_plus)
      space = '+';
    else if (spec_read.flag_space)
      space = ' ';
  }

  spec_read.lenght = fmax(0, spec_read.lenght - num_len - (space != 0));
  if (spec_read.flag_minus || spec_read.flag_zero) {
    if (space != 0) *(ptr++) = space;
    if (spec_read.flag_zero) {
      s21_memset(ptr, '0', spec_read.lenght);
      ptr += spec_read.lenght;
    }
    s21_strncpy(ptr, num_str, num_len);
    ptr += num_len;
    if (spec_read.flag_minus) {
      s21_memset(ptr, ' ', spec_read.lenght);
      ptr += spec_read.lenght;
    }
  } else {
    s21_memset(ptr, ' ', spec_read.lenght);
    ptr += spec_read.lenght;
    if (space != 0) *(ptr++) = space;
    s21_strncpy(ptr, num_str, num_len);
    ptr += num_len;
  }

  return ptr - str;
}

int s_specificator(char *str, specification_read spec_read, char *str2) {
  s21_size_t str_len = s21_strlen(str2);
  if (spec_read.reading_acc) {
    str_len = spec_read.accuracy;
  }
  spec_read.lenght = fmax(0, spec_read.lenght - (int)str_len);
  if (spec_read.flag_minus) {
    s21_strncat(str, str2, str_len);
    s21_memset(str + str_len, ' ', spec_read.lenght);
  } else {
    s21_memset(str, ' ', spec_read.lenght);
    s21_strncat(str + spec_read.lenght, str2, str_len);
  }
  return str_len + spec_read.lenght;
}

void read_flag(char c, specification_read *spec_read, va_list args) {
  if (c == 'h')
    spec_read->flag_h += 1;
  else if (c == 'l')
    spec_read->flag_l += 1;
  else if (c == 'L')
    spec_read->flag_L += 1;
  else if (c == '-')
    spec_read->flag_minus = 1;
  else if (c == '+')
    spec_read->flag_plus = 1;
  else if (c == ' ')
    spec_read->flag_space = 1;
  else if (c == '#')
    spec_read->flag_hash = 1;
  else if (c == '0' && !spec_read->reading_acc && !spec_read->reading_lenght)
    spec_read->flag_zero = 1;
  else if (c == '.')
    spec_read->reading_acc = 1;
  else if (c == '*') {
    if (spec_read->reading_acc)
      spec_read->accuracy = va_arg(args, long long int);
    else {
      spec_read->reading_lenght = 1;
      spec_read->lenght = va_arg(args, long long int);
    }
  } else if ((c > '0' && c <= '9') ||
             (c == '0' &&
              (spec_read->reading_acc || spec_read->reading_lenght))) {
    if (spec_read->reading_acc) {
      spec_read->accuracy *= 10;
      spec_read->accuracy += c - '0';
    } else {
      spec_read->reading_lenght = 1;
      spec_read->lenght *= 10;
      spec_read->lenght += c - '0';
    }
  }
}

specification_read read_flags(int len, const char *format, va_list args) {
  specification_read spec_read = {0};
  for (int i = 0; i < len; i++) {
    read_flag(format[i], &spec_read, args);
  }
  if (spec_read.flag_plus) spec_read.flag_space = 1;

  return spec_read;
}

int read_specificator(char *str, const char *format, int len, char specificator,
                      va_list args, int current_len) {
  specification_read spec_read = read_flags(len, format, args);
  spec_read.spec = specificator;
  char spec_str[1024] = {0};
  int spec_len = 0;
  switch (specificator) {
    case 'c':
      if (spec_read.lenght < 1) spec_read.lenght = 1;
      s21_memset(spec_str, ' ', spec_read.lenght - 1);
      *(spec_str + spec_read.lenght - 1) = va_arg(args, int);
      spec_len += spec_read.lenght;
      break;
    case 'd':
      if (spec_read.accuracy) spec_read.flag_zero = 0;
      if (spec_read.flag_h == 1)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (short int)va_arg(args, int));
      else if (spec_read.flag_h == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (signed char)va_arg(args, int));
      else if (spec_read.flag_l == 1)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long int));
      else if (spec_read.flag_l == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       va_arg(args, long long int));
      else
        spec_len += digit_specificator(spec_str, spec_read, va_arg(args, int));
      break;
    case 'g':
      if (spec_read.accuracy == 0 && !spec_read.reading_acc)
        spec_read.accuracy = 6;
      if (spec_read.flag_L)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long double));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, double));
      break;
    case 'G':
      if (spec_read.accuracy == 0 && !spec_read.reading_acc)
        spec_read.accuracy = 6;
      if (spec_read.flag_L)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long double));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, double));
      break;
    case 'e':
      if (spec_read.accuracy == 0 && !spec_read.reading_acc)
        spec_read.accuracy = 6;
      if (spec_read.flag_L)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long double));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, double));
      break;
    case 'E':
      if (spec_read.accuracy == 0 && !spec_read.reading_acc)
        spec_read.accuracy = 6;
      if (spec_read.flag_L)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long double));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, double));
      break;
    case 'f':
      if (spec_read.accuracy == 0 && !spec_read.reading_acc)
        spec_read.accuracy = 6;
      if (spec_read.flag_L)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long double));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, double));
      break;
    case 'o':
      spec_len +=
          digit_specificator(spec_str, spec_read, va_arg(args, long long int));
      break;
    case 'x':
      if (spec_read.flag_h == 1)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (short int)va_arg(args, long long int));
      else if (spec_read.flag_h == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (char)va_arg(args, long long int));
      else if (spec_read.flag_l == 1)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (long int)va_arg(args, long long int));
      else if (spec_read.flag_l == 2)
        spec_len += digit_specificator(
            spec_str, spec_read, (long long int)va_arg(args, long long int));
      else
        spec_len += digit_specificator(spec_str, spec_read,
                                       va_arg(args, long long int));
      break;
    case 'X':
      spec_len +=
          digit_specificator(spec_str, spec_read, va_arg(args, long long int));
      break;
    case 's':
      spec_len += s_specificator(spec_str, spec_read, va_arg(args, char *));
      break;
    case 'u':
      if (spec_read.flag_h == 1)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (short unsigned int)va_arg(args, int));
      else if (spec_read.flag_h == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (unsigned char)va_arg(args, int));
      else if (spec_read.flag_l == 1)
        spec_len += digit_specificator(
            spec_str, spec_read, (long unsigned int)va_arg(args, long int));
      else if (spec_read.flag_l == 2)
        spec_len += digit_specificator(
            spec_str, spec_read,
            (long long unsigned int)va_arg(args, long long int));
      else
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, unsigned int));
      break;
    case 'i':
      if (spec_read.accuracy) spec_read.flag_zero = 0;
      if (spec_read.flag_h == 1)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (short int)va_arg(args, int));
      else if (spec_read.flag_h == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       (signed char)va_arg(args, int));
      else if (spec_read.flag_l == 1)
        spec_len +=
            digit_specificator(spec_str, spec_read, va_arg(args, long int));
      else if (spec_read.flag_l == 2)
        spec_len += digit_specificator(spec_str, spec_read,
                                       va_arg(args, long long int));
      else
        spec_len += digit_specificator(spec_str, spec_read, va_arg(args, int));
      break;
    case 'p':
      spec_read.flag_hash = 1;
      long long int *ptr = va_arg(args, long long int *);
      long long int b = (long long int)ptr;
      spec_len += hexidecimal_number(spec_str, spec_read, b, 0);
      break;
    case 'n':
      *va_arg(args, long long int *) = current_len;
      break;
    case '%':
      *spec_str = '%';
      spec_len += 1;
      break;
  }

  s21_strncat(str, spec_str, spec_len);

  return spec_len;
}

char *ftos(char *res, long double num, int accuracy, int need_dot) {
  long long int ipart = num;
  char *ptr = res;

  long long int fpart = 0;

  long long int pow = 10;
  for (int i = 0; i < accuracy - 1; i++) pow *= 10;

  fpart = my_round(num * pow) % pow;

  itos(ptr, ipart, 1);
  ptr += s21_strlen(ptr);
  if (need_dot) *(ptr++) = '.';
  if (accuracy > 0) {
    itos(ptr, fpart, accuracy);
  }

  return res;
}

char *utos(char *str, long long unsigned int num, int accuracy) {
  reversed_unsigned_digit(str, num, accuracy);

  reverse_str(str);
  str[s21_strlen(str) + 1] = '\0';

  return str;
}

char *itos(char *str, long long int num, int accuracy) {
  reversed_digit(str, num, accuracy);

  reverse_str(str);
  str[s21_strlen(str) + 1] = '\0';

  return str;
}

char *reversed_unsigned_digit(char *str, long long unsigned int num,
                              int accuracy) {
  int i = 0;
  if (num == 0) str[i++] = '0';
  while ((long long int)num) {
    str[i++] = num % 10 + '0';
    num = num / 10;
  }
  int zeros_count = accuracy - i;
  for (int j = 0; j < zeros_count; j++) str[i++] = '0';

  return str;
}

char *reversed_digit(char *str, long long int num, int accuracy) {
  int i = 0;
  if (num == 0) str[i++] = '0';
  if (num < 0) {
    num *= -1;
  }
  while ((long long int)num) {
    str[i++] = num % 10 + '0';
    num = num / 10;
  }
  int zeros_count = accuracy - i;
  for (int j = 0; j < zeros_count; j++) str[i++] = '0';

  return str;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  char *start = str;

  va_start(args, format);
  char *find = s21_strchr(format, '%');
  while (find != S21_NULL) {
    s21_size_t words_len = find - format;
    s21_strncpy(str, format, words_len);
    str += words_len;
    format = find + 1;
    find = s21_strpbrk(format, specifications);
    str +=
        read_specificator(str, format, find - format, *find, args, str - start);
    format = find + 1;
    find = s21_strchr(format, '%');
  }

  s21_size_t remained = s21_strlen(format);
  s21_strncpy(str, format, remained);
  str += remained;
  return str - start;
}

void read_d(char *str, char *buffer) {
  while (*buffer > '0' && *buffer < '9') {
    *(str++) = *(buffer++);
  }
}

// int sasha_func(char *arr) {
//   int num = 0;
//   int flag_minus = 0;
//   int mult = 1;
//   int len = s21_strlen(arr);
//   len = my_abs((long double)len);

//   while (len--) {
//     if (arr[0] == '-') flag_minus = 1;
//     num += (arr[len] - '0') * mult;
//     mult *= 10;
//   }

//   flag_minus ? -num : num;
//   return num;
// }

// int s21_sscanf(char *buffer, const char *format, ...) {
//   va_list args;
//   va_start(args, format);
//   char *find = s21_strchr(format, '%');
//   while (find != S21_NULL) {
//     char *start = find + 1;
//     find = s21_strpbrk(format, specifications);
//     switch (*find) {
//       case 'd':
//         char str[1024] = "";
//         int *p = va_arg(args, int *);
//         read_d(str, buffer);
//         printf("%s", str);
//         *p = sasha_func(str);
//         break;

//       default:
//         break;
//     }

//     find = s21_strchr(format, '%');
//     format = find + 1;
//   }
//   return 0;
// }
