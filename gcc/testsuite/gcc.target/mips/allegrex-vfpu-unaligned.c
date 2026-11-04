/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math -fdump-tree-vect-details" } */
/* { dg-skip-if "requires -O3" { *-*-* } { "*" } { "-O3" } } */
/* { dg-final { scan-tree-dump {loop vectorized using 16 byte vectors} "vect" } } */
/* { dg-final { scan-assembler {lv[.]s} } } */
/* { dg-final { scan-assembler {vadd[.]q} } } */
/* { dg-final { scan-assembler {sv[.]s} } } */

void
add (float *__restrict d, const float *__restrict a,
     const float *__restrict b, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    d[i] = a[i] + b[i];
}
