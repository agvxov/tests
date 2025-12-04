#!/usr/bin/perl

use strict;
use warnings;
use attributes;
use feature 'signatures';
use Scalar::Util 'refaddr';
use Data::Dumper;

my %attrs;
sub MODIFY_CODE_ATTRIBUTES {
    my ($package, $subref, @attrs) = @_;
    my %known_attributes = map { $_ => 1 } (
        'my_attr'
    );
    $attrs{ refaddr $subref } =
        [ grep { exists $known_attributes{$_}  } @attrs ];
    return grep { !exists $known_attributes{$_}  } @attrs;
}

sub FETCH_CODE_ATTRIBUTES {
    my ($package, $subref) = @_;
    my $attrs = $attrs{ refaddr $subref };
    return @$attrs;
}

sub test : my_attr ($p) {
    print $p . "\n";
}

test("--");
print Dumper( attributes::get(\&test) );
