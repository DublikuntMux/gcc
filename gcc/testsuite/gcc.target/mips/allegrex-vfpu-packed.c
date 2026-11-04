/* { dg-do compile } */
/* { dg-options "-march=allegrex -mabi=32 -EL -mno-mips16 -mno-micromips -mhard-float -msingle-float -mvfpu -ffast-math" } */
/* Byte-aligned memory must not be accessed with aligned VFPU loads
   and stores.  */

typedef float v4sf __attribute__ ((vector_size (16)));
struct __attribute__ ((packed)) packed_vector
{
  char pad;
  v4sf value;
};

void
add (struct packed_vector *d, const struct packed_vector *a,
     const struct packed_vector *b)
{
  d->value = a->value + b->value;
}
