I was experimenting with non-coupled editor hints (vim showing function signatures when hovering over a call).
I was using ctags, which only records the first line of declarations, meaning the following:
```c
void f(int i,
        int h);
```
would result in partial hints defeating the purpose.
This thing was meant to preprocess the input files, *onelining* things,
but I figured it was too much of a hack and too expensive.
