#!/usr/bin/perl

{
local $/;
$_ = <STDIN>;
}

s/^\s*export ([A-Za-z0-9]+)=(.*)/set --export $1 $2/mg;
s/^\s*([A-Za-z0-9]+)=(.*)/set $1 $2/mg;

print $_;
