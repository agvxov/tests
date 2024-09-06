a few days ago i saw this pet project on https://git.peppe.rs/languages/tbsp/tree/examples/code-overview/overview.tbsp
being a DSL fan, i really like the idea.
except seemingly the guy is making a full general purpose interpreter too,
which sentences the project to death.
i have email him about this (response pending)

as i was thinking however i started wondering if bison could do it
given an adaquate lex()

well, the answer is kinda.
if you look at the code, well it works.

problems:
 + bison doesnt know includes so it would have to be preprocessed
    (to provide tokens as -perversily- the scanner defines them)
 + the tree sitter query language is much more...
    well lets say verboser than i imagined, so our code has to be much
    more complexed than i hoped so;
    either the bison programmer has to type a lot or lex()
    define a bunch of wrappers which would be language specific
 + we are not really using the stack are we?
   (unless we do stuff like `BEGIN FUNCTION`/`END FUNCTION`
    to mimic the "original" grammar (which is not bad))
   so its a hack to begin with,
   and because of the above reasons and ugly one of that

so, instead, i do think a DSL is the answer.
only issue is that if the guy disagrees on making it "supplementary"
then i will have to make my own.

one more thing, a ts node query language would also be nice.
something along the lines of
```
$$->declarator
```
expanding to a node object
(or erroring out safely if the "declarator" named field does not exist)
