// @BAKE gcc $@ -o $*.out -O0 -ggdb
signed main() {
    char * src = "hey";
    char dest[4];
    int n = 0;
    int j = 0;
    int i = 0;
    // Duff [8, 13] used this to provide a manual version of loop unrolling for older compilers and hardware:
    switch(n & 0x3) {
      do {
        case 0: dest[i++] = src[j++];
        case 1: dest[i++] = src[j++];
        case 2: dest[i++] = src[j++];
        case 3: dest[i++] = src[j++];
      } while (j < n);
    }
    return 0;
}
