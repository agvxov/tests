main:
	bake program.c
	bake program2.c

test: main
	ORIGIN="$$(realpath .)" PATH="$$(realpath .):$${PATH}" cmdtest
