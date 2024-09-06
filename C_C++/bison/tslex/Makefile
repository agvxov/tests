main:
	bison --header=main.tab.h main.y
	gcc main.tab.c tslex.c $$(pkg-config --cflags --libs tree-sitter tree-sitter-c) -ggdb
