// @BAKE gcc $@ -o $*.out -lmagic
#include <magic.h>
#include <stddef.h> // for NULL

magic_t my_mimetype_reader;

signed main(int argc, char * argv[]) {
    if (argc != 2) {
        printf("%s <file>\n", argv[0]);
        return 1;
    }

	my_mimetype_reader = magic_open(MAGIC_MIME_TYPE);
	if (magic_load(my_mimetype_reader, NULL) == -1) { return 1; }

    // It *is* a const char *; do not try to free it; copy it if you have to
    const char * filename = magic_file(my_mimetype_reader, argv[1]);
    if (filename == NULL) { return 1; }

    puts(filename);

	magic_close(my_mimetype_reader);
    return 0;
}
