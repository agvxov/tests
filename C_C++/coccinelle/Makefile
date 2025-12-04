patch: hot2.cocci
	spatch --sp-file hot2.cocci main2.c -o main-patched.c

so: main2.c
	gcc -fPIC -shared -o libmain-patched.c.so.swp main2.c -std=c23 -ggdb
	mv libmain-patched.c.so.swp libmain-patched.c.so

host: main2.c
	gcc -o main-patched.out main-patched.c -std=c23 -ggdb
