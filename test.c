#include "common.h"

int main(int argc, char *argv[]) {
    uchar *v;
    long long int n, i;

    n = atoll(argv[1]);

    v = allocUCharArray(n, false);

    printf("%d %lld\n",sizeof(uchar),n);
    for(i=0; i<n; i++) v[i] = 't';

    return EXIT_SUCCESS;
}
