/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math -fdelayed-branch" } */
/* { dg-skip-if "requires optimization" { *-*-* } { "-O0" } { "" } } */
/* { dg-final { scan-assembler {vadd[.]q} } } */
/* { dg-final { scan-assembler-not {\t(b[a-z0-9]*|j[a-z]*)\t[^\n]*\n\tvpfx[sdt]\t} } } */

typedef float v4sf __attribute__ ((vector_size (16), aligned (16)));

void
accumulate (v4sf *d, const v4sf *a, const v4sf *b, unsigned int n)
{
  v4sf sum = *a;
  const v4sf addend = *b;
  do
    sum += addend;
  while (--n);
  *d = sum;
}
