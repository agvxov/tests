> foreach <var> in <subject> do <action> done

something like POSIX for,
except blobs are evaluated lazily inside <subject>
with automatic globstar support

obviously, since its not a built in,
it will have to look slightly different,
however, i believe i can still make it look nice

should support basic parallelism