#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

_Static_assert(sizeof(float)==sizeof(unsigned int), "Architecture error");
_Static_assert(sizeof(double)==sizeof(unsigned long long int), "Architeture error double/long int");
_Static_assert(sizeof(long double)==2*sizeof(unsigned long long int), "Architeture error long double/long int");

bool isNumeric(const char *value)
{

  if (value[0] == 0)
    return false;

  const char *list[] = {"inf", "-inf", "+inf", "nan", "-nan", "+nan", NULL}, **lp = list;

  while (*lp)
    if (strcasecmp(*(lp++), value) == 0)
      return true;

  char c = (char)*(value);

  if (c == 'E' || c == 'e')
    return false;

  bool scientifcNotationOccur = false;
  bool dotOccur = false;

part2:

  if (c == '+' || c == '-')
    if ((c = (char)*(++value)) == 0)
      return false;

  do {
    if (c < '0') {
      if (c == '.')
        if (!dotOccur) {
          dotOccur = true;
          continue;
        }

      return false;
    }

    if (c > '9') {

      if ((c != 'E') && (c != 'e'))
        return false;

      if (!scientifcNotationOccur)
        if ((c = (char)*(++value))) {
          scientifcNotationOccur = true;
          goto part2;
        }

      return false;
    }

  } while ((c = (char)*(++value)));

  return true;
}

int main(int argc, char **argv)
{
    const char *num_arg;

    union value_u {
        unsigned int i;
        float f;
        unsigned long long int l;
        double d;
        struct long_double_part_t {
          long long unsigned int p1;
          unsigned short int p2;
        } long_double_part;
        long double ld;
    } value;

#define VALUE_U_SZ sizeof(union value_u)

    if (argc==1) {
        printf("\nIEEE 754 converter:\n\tType: i3ecnv <double value>\n\n");
        return 0;
    } else if (argc>2) {
        printf("\nToo many aguments\n");
        return -1;
    }

    num_arg=(const char *)argv[1];

    if (!isNumeric(num_arg)) {
      printf("\n\"%s\" is not a number\n", num_arg);
      return -2;
    }

    memset(&value, 0, VALUE_U_SZ);

    value.ld=strtold(num_arg, NULL);

    printf("\nValue LONG DOUBLE = %16.016Lf -> 0x%04X%016llX\n", value.ld, value.long_double_part.p2, value.long_double_part.p1);

    memset(&value, 0, VALUE_U_SZ);

    value.d=strtod(num_arg, NULL);

    printf("\nValue DOUBLE = %16.016lf -> 0x%016llX\n", value.d, value.l);

    memset(&value, 0, VALUE_U_SZ);

    value.f=strtof(num_arg, NULL);

    printf("\nValue FLOAT = %16.016f -> 0x%08X\n", value.f, value.i);

    return 0;
}

