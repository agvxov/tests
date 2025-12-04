#!/usr/bin/perl

use strict;
use warnings;
use Sub::Identify ':all';

sub wrap {
    my ($glob, $c_wrapper) = @_;
    no strict 'refs';
    no warnings 'redefine';
    *$glob = $c_wrapper;
}

sub MODIFY_CODE_ATTRIBUTES {
    my ($pkg, $ref, @attrs) = @_;
    my @r;

    my $glob = sub_fullname($ref);

    for my $i (@attrs) {
        if ($i eq 'Italic') {
            wrap $glob => sub { "\033[3m" . $ref->() . "\033[m" };
        } elsif ($i eq 'Bold') {
            wrap $glob => sub { "\033[1m" . $ref->() . "\033[m" };
        } else {
            push(@r, $i);
        }
    }

    return @r;
}

sub hello : Italic Bold  {
    return "hello world\n";
}

print hello();
