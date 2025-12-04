#!/usr/bin/perl

use strict;
use warnings;
use Symbol qw(delete_package);
use FCGI;
BEGIN {
    require CGI::Tiny;
};

my $socket_path = "cgi-tiny-fcgi.sock";
my $socket = FCGI::OpenSocket($socket_path, 5);  # backlog 5

my $in  = \*STDIN;
my $out = \*STDOUT;
my $err = \*STDERR;

my $request = FCGI::Request($in, $out, $err, \%ENV, $socket);

our $counter = 1;

while ($request->Accept() >= 0) {
    &CGI::Tiny::cgi(sub {
        my $cgi = $_;
        $cgi->set_response_status(200)->render(html => "Hello, world $$ # " . $counter++ . "\n");
    });
}
