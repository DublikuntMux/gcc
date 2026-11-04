/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EB -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu" } */
/* { dg-error "requires little-endian uncompressed .*Allegrex o32" "" { target *-*-* } 0 } */

int x;
