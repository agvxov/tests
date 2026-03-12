# Minimal recriation of what Reply does
use Eval::Closure 0.11;

say 'test';

my $code = eval_closure(
    source      => "sub {\nsay 'test';\n}",
    terse_error => 1,
);

print $code;

# $ perl -mfeature=say eval_closure.pl
# test
# String found where operator expected (Do you need to predeclare "say"?) at (eval 5) line 4, near "say 'test'"
# syntax error at (eval 5) line 4, near "say 'test'"
# Execution of (eval 5) aborted due to compilation errors.
