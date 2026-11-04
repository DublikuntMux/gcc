/* { dg-do compile } */
/* { dg-options "-march=mips2 -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu" } */
/* { dg-error "requires little-endian uncompressed .*Allegrex o32" "" { target *-*-* } 0 } */

int x;
