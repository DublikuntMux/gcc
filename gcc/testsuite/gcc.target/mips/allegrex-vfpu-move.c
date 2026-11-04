/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math" } */
/* { dg-final { scan-assembler {lv[.]s} } } */
/* { dg-final { scan-assembler {sv[.]s} } } */

typedef float v4sf __attribute__ ((vector_size (16), aligned (4)));

void
add (v4sf *d, const v4sf *a, const v4sf *b)
{
  *d = *a + *b;
}

void
clear (v4sf *d)
{
  *d = (v4sf) { 0, 0, 0, 0 };
}

void
construct (v4sf *d, float a, float b, float c, float e)
{
  *d = (v4sf) { a, b, c, e };
}
