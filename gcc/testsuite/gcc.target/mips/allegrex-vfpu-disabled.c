/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mno-vfpu -ffast-math" } */
/* { dg-skip-if "requires -O3" { *-*-* } { "*" } { "-O3" } } */
/* { dg-final { scan-assembler {add[.]s} } } */
/* { dg-final { scan-assembler-not {vadd[.]q} } } */

void
add (float *__restrict d, const float *__restrict a,
     const float *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] + b[i];
}

void
subtract (float *__restrict d, const float *__restrict a,
          const float *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] - b[i];
}

void
multiply (float *__restrict d, const float *__restrict a,
          const float *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] * b[i];
}
/* { dg-final { scan-assembler-not {v(sub|mul)[.]q} } } */
