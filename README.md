# alcvx
Aligned C Vector Extension single-header math library

## Status

### DONE
- integral scalar types i.e. f32, f64, b8, u8, s8, i8, c8
- arbitrary length vec(t,n) and vec_ext(t,n) power of two types and ALCVX load/cast
- bitceil, isarray, countof, countargs, emptyargs, perm
- OpenMP SIMD linear dot product and sum
- vec(t,n) cross3 product using perm3

### TODO
- use bit_ceil and align modes
- array initializer list duplicate for copy assign
- determinant, laplace expansion and cross4 
- levi-civita symbol
- generic n-dim hodge star operator
- motor/rotor/quat and oct/sed/ten types

```c
vec(f32,3) a = {4,2,0};
vec(f32,3) b = dup(a);
```

## Usage

```c
#include <stdlib.h>
#include <stdio.h>
#include <alcvx.h>

int main(int argc, char** argv)
{
     vec3_t src = { 1,2,3 };
    avec3_t dst = ALCVX(src,3);

    dst *= ALCVX(src,3);
    src = dst;
    exit(EXIT_SUCCESS);
}
```

```sh
[1.000000 2.000000 3.000000 0.000000]  4/12
[1.000000 4.000000 9.000000 0.000000] 16/16
[1 2 3 0]  8/ 8
```
