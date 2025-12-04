# Bashed decommissioning
The initial motivation was,
that bash is too hard to configure.
Since I've come to the conclusion that that is a side effect of Bash being shit.

### Bash's faults
* no verbose form to all of its magicks; after long years, i keep forgetting half of it;
im sure some system admin loves the short forms, but there should be an alternative
for the mortals
* complex grammar instead of more builtins
* no builtin culture which i assume stems from poor builtin support;
for example, grep, the executable *should be* trivial to make into a builtin,
which would result in real performance gains when it happens to run under bash;
perhaps im wrong on this
* Tcl simply has a better syntax; it solves all of the word splitting problems;
while providing what is essentially a portable(/exportable) list construct
(something bash has not)
* it uses readline, which is its own can of worms;
but briefly, its bloated,
yet reverse search, completion, multi line editing and syntax highlighting
are either shit or missing
* tons of obscure features

### Futures
* i want to make my own shell, which is minimal, flexible and is based on Tcl
