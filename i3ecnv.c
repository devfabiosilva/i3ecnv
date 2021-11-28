#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

_Static_assert(sizeof(float)==sizeof(unsigned int), "Architecture error");
_Static_assert(sizeof(double)==sizeof(unsigned long long int), "Architeture error double/long int");

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
    memset(&value, 0, VALUE_U_SZ);

    value.d=strtod(num_arg, NULL);

    printf("\nValue DOUBLE = %lf -> 0x%016llX\n", value.d, value.l);

    memset(&value, 0, VALUE_U_SZ);

    value.f=strtof(num_arg, NULL);

    printf("\nValue FLOAT = %lf -> 0x%08X\n", value.f, value.i);

    return 0;
}
