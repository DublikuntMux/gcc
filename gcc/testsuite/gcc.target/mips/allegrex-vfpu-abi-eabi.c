/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=eabi -mgp32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math" } */
/* Exercise transfers between VFPU registers and the o32 argument and
   return registers, including arguments split between registers and stack.  */
/* { dg-final { scan-assembler {vadd[.]q} } } */

typedef float v4sf __attribute__ ((vector_size (16)));

extern v4sf callee (int, v4sf, v4sf);

v4sf
add (int ignored, v4sf a, v4sf b)
{
  return a + b;
}

v4sf
call (v4sf a, v4sf b)
{
  return callee (1, a, b);
}
