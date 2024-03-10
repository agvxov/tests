main:
	gcc -shared thing.c -o libthing.so
	gfortran main.f95 -o main.out -L. -lthing

run:
	export LD_LIBRARY_PATH=$$(realpath .):$${LD_LIBRARY_PATH}; \
	./main.out
