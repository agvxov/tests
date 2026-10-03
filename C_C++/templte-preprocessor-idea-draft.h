// .h
// this tells the preprocessor that this is a signature we could instantiate
template<typename T>
size_t strlist_len(const char *, T sep);

// this tells the preprocessor that we want to instantiate our signature with char
template extern strlist_len<char>;

// .c
// this is our actual template function
// note that strlist_find itself would be a generic, likely defined by hand
template<typename T>
size_t strlist_len(const char *, T sep) {
    assert(list);

    const char * s = list;

    if (s[0] == '\0') { return 0; }

    if (strlist_find(s, sep) == 0) { ++s; }

    size_t r = 1;
    while ((s = strlist_find(s, sep))) {
        ++s;
        ++r;
    }
    return r;
}

// this tells the preprocessor to produce a function from the above
template strlist_len<char>;

/* notes:
 * - this technique is comprehensable, you can tell exactly what is going on
 * - this is only possible because of _Generic,
 *   which is something cfront did not have access to
 * - the preprocessor does not actually need to be type aware
 * - this preprocessor is in a perpetual war with the default one,
 *   because it has to expand beforehand, but it cannot tell if expanding a macro
 *   results in new controls blocks which would influence where a function ends
 * - i have not actaully come up with a syntax of creating the _Generic macro
 *   that would wrap the variants
 * - how would the user extend this anyways?
 */
