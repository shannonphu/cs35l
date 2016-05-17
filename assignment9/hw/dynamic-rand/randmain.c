#include "randcpuid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (void);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  void *lib;
  char * err;
  
  if (rdrand_supported ())
    {
      lib = dlopen("randlibhw.so", RTLD_NOW);
      if (!lib) {
	printf("failed to open randlibhw.so: %s \n", dlerror());
	exit(1);
      }

      initialize = dlsym(lib, "hardware_rand64_init");
      err = dlerror();
      if (err) {
	printf("failed to locate hardware_rand64_init: %s \n", err);
	exit(1);
      }
      initialize();

      rand64 = dlsym(lib, "hardware_rand64");
      err = dlerror();
      if (err) {
	printf("failed to locate hardware_rand64: %s \n", err);
	exit(1);
      }

      finalize =  dlsym(lib, "hardware_rand64_fini");
      err = dlerror();
      if (err) {
	printf("failed to locate hardware_rand64_fini: %s \n", err);
	exit(1);
      }
      finalize();
    }
  else
    {
      lib = dlopen("randlibsw.so", RTLD_NOW);
      if (!lib) {
	printf("failed to open randlibsw.so: %s \n", dlerror());
	exit(1);
      }

      initialize = dlsym(lib, "software_rand64_init");
      err = dlerror();
      if (err) {
	printf("failed to locate software_rand64_init: %s \n", err);
	exit(1);
      }

      rand64 = dlsym(lib, "software_rand64");
      err = dlerror();
      if (err) {
	printf("failed to locate software_rand64: %s \n", err);
	exit(1);
      }

      finalize =  dlsym(lib, "software_rand64_fini");
      err = dlerror();
      if (err) {
	printf("failed to locate software_rand64_fini: %s \n", err);
	exit(1);
      }
    }

  //  initialize ();
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      size_t outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (fwrite (&x, 1, outbytes, stdout) != outbytes)
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
      finalize ();
      return 1;
    }

  dlclose(lib);
  //  finalize ();
  return 0;
}
