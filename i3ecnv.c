#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

_Static_assert(sizeof(float)==sizeof(unsigned int), "Architecture error");
_Static_assert(sizeof(double)==sizeof(unsigned long long int), "Architeture error double/long int");

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
  bool occur = false;

part2:

  if (c == '+' || c == '-')
    if ((c = (char)*(++value)) == 0)
      return false;

  do {
    if (c < '0') {
      if (c == '.')
        if (!occur) {
          occur = true;
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
      printf("\n%s is not a number\n", num_arg);
      return -2;
    }

    memset(&value, 0, VALUE_U_SZ);

    value.d=strtod(num_arg, NULL);

    printf("\nValue DOUBLE = %lf -> 0x%016llX\n", value.d, value.l);

    memset(&value, 0, VALUE_U_SZ);

    value.f=strtof(num_arg, NULL);

    printf("\nValue FLOAT = %lf -> 0x%08X\n", value.f, value.i);

    return 0;
}

