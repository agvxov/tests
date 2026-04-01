# fzfind #
> fzf based file fuzzy finder for Bash

![](showoff.gif)

### What it does ###
fzfind will:
+ use fzf to prompt for the file desired by the user
+ show the line typed so far with the point of insertion marked
+ take the path typed so far into account
+ quote the result
+ use either `find` or `locate`, ensuring usability on slower drives

### Configuration ###

**$FZFINDMETHOD**

Specifies what utility to use for file searches.
Possible values:
+ find
+ locate

**$FZFINDDOBIND**

Bind fzfind to `ctrl+f`.
The default behaviour is to do so.
If this is not the desired,
set it to `false` in your bashrc before evaluating fzfind.

### Dependencies ###
+ GNU coreutils
+ fzf

NOTE: fzfind uses the extra-minimalistic `lastword` executable
to determine what portion of the line typed so far is a
directory prefix.
This information is for narrowing down the results

### Instalation ###
1. Run `make install` (to compile the last word finder C program and move it into your $PATH)
2. Source `fzfind.rc` from your `.bashrc` or copy its contents directly into it
