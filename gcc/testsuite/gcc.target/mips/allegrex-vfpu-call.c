/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math" } */
/* A value live across an external call must be spilled and reloaded;
   o32 does not guarantee 16-byte stack alignment.  */
/* { dg-final { scan-assembler {vadd[.]q} } } */
/* { dg-final { scan-assembler {l(v[.]s|w)} } } */
/* { dg-final { scan-assembler {s(v[.]s|w)} } } */

typedef float v4sf __attribute__ ((vector_size (16), aligned (16)));

extern void clobber (void);

void
add_across_call (v4sf *d, const v4sf *a, const v4sf *b)
{
  v4sf sum = *a + *b;
  clobber ();
  *d = sum + *b;
}
