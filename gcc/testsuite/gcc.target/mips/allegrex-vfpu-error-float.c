/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -msoft-float -msingle-float -mvfpu" } */
/* { dg-error "requires .*mhard-float.* and .*msingle-float" "" { target *-*-* } 0 } */

int x;
