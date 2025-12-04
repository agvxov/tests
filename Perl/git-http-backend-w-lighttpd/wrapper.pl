#!/usr/bin/perl

use strict;
use warnings;
use feature 'signatures';
use IPC::Open3;
use Symbol 'gensym';

# Maybe this fucks with the process?
#  YES YES IT DOES AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
#use CGI;
#my $cgi = CGI::new;
# --
BEGIN {
    require CGI::Tiny;
}
use FCGI;
# but, atleast, CGI::Tiny and FCGI are fine
# --

# NOTE: depending on the lighttpd config,
#        $PATH_INFO and $QUERY_STRING might not be set

# NOTE: $repo, $tail and $param was for when i tried to hand craft $PATH_INFO
sub serve_git_http_backend ($repo, $tail, $param) {
    $ENV{GIT_PROJECT_ROOT}    = "/home/anon/Swap/git-http-backend-w-lighttpd/";
    $ENV{GIT_HTTP_EXPORT_ALL} = '1';

    # Does not seem to matter
    #binmode(STDIN);
    #binmode(STDOUT);
    #binmode(STDERR);

    ##my $pid = open3(\*STDIN, \*STDOUT, \*STDERR, "/home/anon/Swap/git/git-http-backend");
    #my $err = gensym;
    #my $pid = open3(undef, \*CHLD_OUT, $err, "/home/anon/Swap/git/git-http-backend");
    #print $_ while <CHLD_OUT>;
    #print $_ while <$err>;
    #waitpid($pid, 0);

    print STDERR "> $ENV{PATH_INFO}\n";
    print STDERR "> $ENV{QUERY_STRING}\n";

    exec "/home/anon/Swap/git/git-http-backend";
}

# --
my $socket_path = "cgi-tiny-fcgi.sock";
my $socket = FCGI::OpenSocket($socket_path, 5);  # backlog 5

my $in  = \*STDIN;
my $out = \*STDOUT;
my $err = \*STDERR;

my $request = FCGI::Request($in, $out, $err, \%ENV, $socket);
# --

while ($request->Accept() >= 0) {
    &CGI::Tiny::cgi(sub {
#cgi {
$_ = $ENV{'REQUEST_URI'} || '/';
m|/([\w]+)\.git(.*)(\?.*)|;
serve_git_http_backend($1, $2, $3);
#};
}
