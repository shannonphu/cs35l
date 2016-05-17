
randmain: randcpuid.o randmain.o
	$(CC) $(CFLAGS) -g -ldl -Wl,-rpath=$(PWD) randcpuid.o randmain.o -o randmain

randlibhw.so: randlibhw.c
	$(CC) $(CFLAGS) randlibhw.c -fPIC -shared -o randlibhw.so

randlibsw.so: randlibsw.c
	$(CC) $(CFLAGS) randlibsw.c -fPIC -shared -o randlibsw.so
