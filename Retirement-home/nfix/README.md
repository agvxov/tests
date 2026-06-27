# nfix
When an ncurses program crashes,
it makes the terminal settings go up in flames.
nfix restores the last buffer and brings I/O settings to a usable state.

### Retirement
I realised that there is a standard (but not POSIX lol)
program for this called `reset`.
