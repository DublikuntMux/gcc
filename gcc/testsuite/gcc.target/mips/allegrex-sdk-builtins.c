/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float" } */
/* { dg-additional-options "-Werror=implicit-function-declaration" } */

/* Check the intrinsics used by PSPSDK's math and network headers.  The
   conversion results are integers transferred from the scalar FPU.  */
int ceil_s (float x) { return __builtin_allegrex_ceil_w_s (x); }
int floor_s (float x) { return __builtin_allegrex_floor_w_s (x); }
int round_s (float x) { return __builtin_allegrex_round_w_s (x); }
int trunc_s (float x) { return __builtin_allegrex_trunc_w_s (x); }
float sqrt_s (float x) { return __builtin_allegrex_sqrt_s (x); }
unsigned short swap_h (unsigned short x) { return __builtin_allegrex_wsbh (x); }
unsigned int swap_w (unsigned int x) { return __builtin_allegrex_wsbw (x); }

/* { dg-final { scan-assembler-times {ceil[.]w[.]s} 1 } } */
/* { dg-final { scan-assembler-times {floor[.]w[.]s} 1 } } */
/* { dg-final { scan-assembler-times {round[.]w[.]s} 1 } } */
/* { dg-final { scan-assembler-times {trunc[.]w[.]s} 1 } } */
/* { dg-final { scan-assembler-times {sqrt[.]s} 1 } } */
/* { dg-final { scan-assembler-times {mfc1} 4 } } */
/* { dg-final { scan-assembler-times {wsbh} 1 } } */
/* { dg-final { scan-assembler-times {wsbw} 1 } } */
/* { dg-final { scan-assembler-not {__builtin_allegrex_} } } */
