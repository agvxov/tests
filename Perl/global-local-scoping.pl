#!/usr/bin/perl

our $global;

print "> $global\n";

sub b {
    print ">> $global\n";
}

sub a {
    local $global = 33;
    b;
}
a;

print "> $global\n";
