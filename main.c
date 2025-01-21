#include "s21_string.h"

int main(){
    int x = 0;
    s21_sscanf("1234", "%d", &x);
    printf("\n%d", x);
    return 0;
}