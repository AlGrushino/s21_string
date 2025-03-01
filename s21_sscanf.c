#include "s21_string.h"


int read_d(char *str, char *buffer, int width) {
  int width_count = 0;
  int flag_minus = 0;
  int counter = 0;
  if (width == 0) width = 1024;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  } else if (buffer[0] == '+') {
    counter++;
    buffer++;
    width_count++;
  }
  while (((*buffer >= '0' && *buffer <= '9') || *buffer == '-') &&
         (width_count < width) && !flag_minus) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
    if (*buffer == '-') flag_minus++;
  }
  return counter;
}

int read_c(char *str, char *buffer, int width) {
  if (width == 0) {
    width = 1;
  }
  int width_count = 0;
  int counter = 0;
  while (width_count < width) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
  }
  return counter;
}

int read_f(char *str, char *buffer, int width) {
  int flag_point = 0;
  int width_count = 0;
  int flag_minus = 0;
  int counter = 0;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  } else if (buffer[0] == '+') {
    counter++;
    buffer++;
    width_count++;
  }
  if (width == 0) width = 1024;
  while (((*buffer >= '0' && *buffer <= '9') || *buffer == '.' ||
          *buffer == '-') &&
         (flag_point) < 2 && (width_count < width) && flag_minus == 0) {
    if (*buffer == '.') (flag_point)++;
    if (*buffer == '0') flag_minus++;
    *(str++) = *(buffer++);
    width_count++;
    counter++;
  }
  return counter;
}

int read_s(char *str, char *buffer, int width) {
  int width_count = 0;
  int counter = 0;
  if (width == 0) width = 1024;
  while (*buffer != ' ' && (width_count < width)) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
  }
  //*(str++) = '\0';
  return counter;
}

int read_e(char *str, char *buffer, int width) {
  int flag_point = 0;
  int width_count = 0;
  int flag_e = 0;
  int counter = 0;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  }
  if (width == 0) width = 1024;
  while (((*buffer >= '0' && *buffer <= '9') || *buffer == '.' ||
          *buffer == 'E' || *buffer == 'e' || *buffer == '+' ||
          *buffer == '-') &&
         (flag_point) < 2 && (width_count < width)) {
    if (*buffer == '.') flag_point++;
    if (*buffer == 'E' || *buffer == 'e') flag_e++;
    width_count++;
    counter++;
    if (flag_e > 1)
      width_count = width;
    else
      *(str++) = *(buffer++);
  }
  return counter;
}

int read_x(char *str, char *buffer, int width) {
  int width_count = 0;
  int flag_minus = 0;
  int counter = 0;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  }
  if (width == 0) width = 1024;
  while (((*buffer >= '0' && *buffer <= '9') || *buffer == '-' ||
          (*buffer >= 'a' && *buffer <= 'f') ||
          (*buffer >= 'A' && *buffer <= 'F') || *buffer == 'x') &&
         (width_count < width) && !flag_minus) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
    if (*buffer == '-') flag_minus++;
  }
  return counter;
}

int read_8(char *str, char *buffer, int width) {
  int width_count = 0;
  int flag_minus = 0;
  int counter = 0;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  }
  if (width == 0) width = 1024;
  while (((*buffer >= '0' && *buffer <= '7') || *buffer == '-' ||
          *buffer == 'x') &&
         (width_count < width) && !flag_minus) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
    if (*buffer == '-') flag_minus++;
  }

  return counter;
}

int read_u(char *str, char *buffer, int width) {
  int width_count = 0;
  int flag_minus = 0;
  if (width == 0) width = 1024;
  int counter = 0;
  if (buffer[0] == ' ') {
    while (*buffer == ' ') {
      counter++;
      buffer++;
    }
  }
  while (((*buffer >= '0' && *buffer <= '9') || *buffer == '-') &&
         (width_count < width) && !flag_minus) {
    *(str++) = *(buffer++);
    width_count++;
    counter++;
    if (*buffer == '-') flag_minus++;
  }
  return counter;
}

typedef struct {
  int width;
  int len_width_str;
  int h;
  int l;
  int L;
  int star;
} after_percentage;

long s21_atoi(char *arr) {
  long num = 0;
  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 10;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

long double s21_atof(char *arr) {
  long double res = 0;
  int flag_minus = 0;
  int i = 0, point = (int)s21_strlen(arr);
  if (arr[0] == '-') {
    flag_minus++;
    i++;
  }
  for (; arr[i] != '\0'; i++) {
    if (arr[i] == '.') point = i;
    if (i < point && arr[i] != '-') {
      res *= 10;
      res += (arr[i] - '0');
    } else if (i != point) {
      res += (float)(arr[i] - '0') / (pow(10, i - point));
    }
  }
  if (flag_minus) {
    res = -res;
  }
  return res;
}

long double s21_atoe(char *arr) {
  long double res = 0;
  int flag_minus = 0;
  long int period_int;

  int i = 0, point = (int)s21_strlen(arr);
  if (arr[0] == '-') {
    flag_minus++;
    i++;
  }
  for (; arr[i] != '\0' && arr[i] != 'e' && arr[i] != 'E'; i++) {
    if (arr[i] == '.') point = i;
    if (i < point && arr[i] != '-') {
      res *= 10;
      res = (arr[i] - '0');
    } else if (i != point) {
      res += (float)(arr[i] - '0') / (pow(10, i - point));
    }
  }
  if (arr[i] == 'e' || arr[i] == 'E') {
    i++;
    arr = arr + i;
    period_int = s21_atoi(arr);
    res = res * pow(10, period_int);
  }
  if (flag_minus) {
    res = -res;
  }
  return res;
}

long int s21_itoa(char *arr) {
  long int num = 0;
  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] >= 'a' && arr[len] <= 'z') arr[len] ^= 0x20;
    if (len == 0 && arr[len] == 0 && arr[len + 1] == 'X')
      ;
    else if ((arr[len] >= '0' && arr[len] <= '9') && arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 16;
    } else if ((arr[len] >= 'A' && arr[len] <= 'F')) {
      num += (arr[len] - 'A' + 10) * mult;
      mult *= 16;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

long int s21_atoi8(char *arr) {
  long int num = 0;
  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 8;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

unsigned long int s21_itoa_unsigned(char *arr) {
  unsigned long int num = 0;
  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] >= 'a' && arr[len] <= 'f') arr[len] ^= 0x20;
    if ((arr[len] >= '0' && arr[len] <= '9') && arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 16;
    } else if ((arr[len] >= 'A' && arr[len] <= 'F')) {
      num += (arr[len] - 'A' + 10) * mult;
      mult *= 16;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

unsigned long int s21_atoi_unsigned(char *arr) {
  unsigned long int num = 0;
  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 8;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

unsigned long int s21_atou(char *arr) {
  unsigned long int num = 0;

  int flag_minus = 0;
  int mult = 1;
  int len = s21_strlen(arr);
  len = my_abs((long double)len);
  if (arr[0] == '-') flag_minus = 1;
  while (len--) {
    if (arr[len] != '-') {
      num += (arr[len] - '0') * mult;
      mult *= 10;
    }
  }
  if (arr[0] == '-') {
    flag_minus = 1;
  }
  if (flag_minus) {
    num = -num;
  }
  return num;
}

void read_percentage(after_percentage *structure, char *start) {
  char width_str[1024] = "";
  if (*(start) == '*') {
    structure->star = 1;
    start += 1;
  }
  int count_symbols = read_d(width_str, start, 0);
  structure->len_width_str = s21_strlen(width_str);
  structure->width = s21_atoi(width_str);
  start += count_symbols;
  switch (*start) {
    case 'l': {
      structure->l = 1;
      break;
    }
    case 'L': {
      structure->L = 1;
      break;
    }
    case 'h': {
      structure->h = 1;
      break;
    }
    default: {
      break;
    }
  }
}

void skip_whitespace(char **str, int *counter) {
  while (**str &&
         (**str == ' ' || **str == '\t' || **str == '\n' || **str == '\r')) {
    (*str)++;
    *counter = *counter + 1;
  }
}

int s21_sscanf(char *buffer, char *format, ...) {
  va_list args;
  va_start(args, format);
  char *find = s21_strchr(format, '%');
  int temp_width = 0;
  int counter = 0;
  int count_success = 0;
  int flag_last_percent = 0;
  while (find != S21_NULL && !flag_last_percent) {
    if (s21_strlen(find) != 1)
      find++;
    else
      flag_last_percent = 1;
    after_percentage percent = {0};
    read_percentage(&percent, find);
    temp_width = percent.width;
    if (s21_strpbrk(find, specifications) != S21_NULL)
      find = s21_strpbrk(find, specifications);
    else
      flag_last_percent = 1;
    if (*find != 'c') skip_whitespace(&buffer, &counter);
    if (s21_strlen(buffer) == 0) {
      count_success = -1;
    }
    switch (*find) {
      case 'd': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_d(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.l) {
            long *p = va_arg(args, long *);
            *p = s21_atoi(str);
          } else {
            int *p = va_arg(args, int *);
            *p = s21_atoi(str);
            if (percent.h) *p = (short)*p;
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'f': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_f(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.L) {
            long double *p = va_arg(args, long double *);
            *p = s21_atof(str);
          } else {
            float *p = va_arg(args, float *);
            *p = s21_atof(str);
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'c': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_c(str, buffer, temp_width);
        if (!percent.star) {
          char *p = va_arg(args, char *);
          s21_strncpy(p, str, s21_strlen(str));
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 's': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_s(str, buffer, temp_width);
        if (!percent.star) {
          char *p = va_arg(args, char *);
          s21_strncpy(p, str, s21_strlen(str));
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'E':
      case 'e': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_e(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.L) {
            long double *p = va_arg(args, long double *);
            *p = s21_atoe(str);
          } else {
            float *p = va_arg(args, float *);
            *p = s21_atof(str);
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'G':
      case 'g': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_e(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.L) {
            long double *p = va_arg(args, long double *);
            if (s21_strchr(str, 'e') || s21_strchr(str, 'E')) {
              *p = s21_atoe(str);
            } else {
              *p = s21_atof(str);
            }
          } else {
            float *p = va_arg(args, float *);
            if (s21_strchr(str, 'e') || s21_strchr(str, 'E')) {
              *p = s21_atoe(str);
            } else {
              *p = s21_atof(str);
            }
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'X':
      case 'x': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_x(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.l) {
            unsigned long *p = va_arg(args, unsigned long *);
            *p = s21_itoa_unsigned(str);
          } else {
            unsigned int *p = va_arg(args, unsigned int *);
            *p = s21_itoa_unsigned(str);
            if (percent.h) *p = (unsigned short)*p;
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'i': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_x(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.l) {
            long *p = va_arg(args, long *);
            if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
              *p = s21_itoa(str);
            else if (str[0] == '0') {
              s21_memset(str, '\0', s21_strlen(str));
              temp_counter = read_8(str, buffer, temp_width);
              *p = s21_atoi8(str);
            } else
              *p = s21_atoi(str);
          } else {
            int *p = va_arg(args, int *);
            if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
              *p = s21_itoa(str);
            else if (str[0] == '0') {
              s21_memset(str, '\0', s21_strlen(str));
              temp_counter = read_8(str, buffer, temp_width);
              *p = s21_atoi8(str);
            } else
              *p = s21_atoi(str);
            if (percent.h) *p = (short)*p;
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'p': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_x(str, buffer, temp_width);
        if (!percent.star) {
          int *p = va_arg(args, void *);
          *p = s21_itoa(str);
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'o': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_8(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.l) {
            unsigned long *p = va_arg(args, unsigned long *);
            *p = s21_atoi_unsigned(str);
          } else {
            unsigned int *p = va_arg(args, unsigned int *);
            *p = s21_atoi_unsigned(str);
            if (percent.h) *p = (unsigned short)*p;
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'u': {
        char str[1024] = "";
        int temp_counter;
        temp_counter = read_u(str, buffer, temp_width);
        if (!percent.star) {
          if (percent.l) {
            unsigned long *p = va_arg(args, unsigned long *);
            *p = s21_atou(str);
          } else {
            unsigned int *p = va_arg(args, unsigned int *);
            *p = s21_atou(str);
            if (percent.h) *p = (unsigned short)*p;
          }
          count_success++;
        }
        buffer = buffer + temp_counter;
        counter += temp_counter;
        break;
      }
      case 'n': {
        if (!percent.star) {
          int *p = va_arg(args, int *);
          *p = counter;
          count_success++;
        }
        counter = 0;
        break;
      }
      default: {
        break;
      }
    }
    format = find;
    find = s21_strchr(format, '%');
  }
  return count_success;
}
