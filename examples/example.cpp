#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
    vec(u16,3)   a[2] = { { 1,2,3 }, { 4,5,6 } };
    vec(u16,3) tmp;
    dup_ext(tmp,a[0]);
    printf("[%hu %hu %hu %hu] %2zu/%2zu %hu %hu\n", tmp[0], tmp[1], tmp[2], tmp[3], alignof(tmp), countof(tmp) * sizeof(typeof(tmp[0])), sum3(tmp), dot3(tmp,a[0]));
    
    exit(EXIT_SUCCESS);
}
