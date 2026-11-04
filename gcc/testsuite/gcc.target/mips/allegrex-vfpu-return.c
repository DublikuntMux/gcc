/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=eabi -mgp32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math" } */
/* EABI hidden return buffers and invisible reference arguments can have
   only stack alignment, even though the vector type is 16-byte aligned.  */
/* { dg-final { scan-assembler {vadd[.]q} } } */
/* { dg-final { scan-assembler {sv[.]s} } } */
/* { dg-final { scan-assembler-not {sv[.]q} } } */

/* { dg-final { scan-assembler-not {[ls]v[.]q[^\n]*\(\$(sp|fp)\)} } } */

typedef float v4sf __attribute__ ((vector_size (16)));

__attribute__ ((noipa)) v4sf
sum (v4sf a, v4sf b)
{
  return a + b;
}

v4sf
relay (v4sf a, v4sf b)
{
  v4sf value = sum (a, b);
  return value + a;
}
