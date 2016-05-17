#include "randlib.h"
#include <stdlib.h>
#include <stdio.h>

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
__attribute__((constructor))
void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (urandstream == NULL) {
    fprintf(stderr, "Cant open /dev/urandom\n");
    abort ();
  }
}

/* Return a random value, using software operations.  */
unsigned long long software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1) {
    fprintf(stderr, "Cant read file made from /dev/urandom\n");
    abort ();
  }
  return x;
}

/* Finalize the software rand64 implementation.  */
__attribute__((destructor))
void
software_rand64_fini (void)
{
  fclose (urandstream);
}

