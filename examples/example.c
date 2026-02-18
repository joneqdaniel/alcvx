#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
    vec(u16,3) tmp = { 1,2,3 }; 
    printf("[%hu %hu %hu %hu] %2zu/%2zu\n", tmp[0], tmp[1], tmp[2], tmp[3], alignof(tmp), countof(tmp) * sizeof(typeof(tmp[0])));
    
    exit(EXIT_SUCCESS);
}
