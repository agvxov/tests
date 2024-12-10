#!/usr/bin/env perl
use strict;
use warnings;
use Cwd;
use Mojolicious::Lite;

get '/' => sub {
    my $c = shift;

    my $cwd = getcwd();
    my @file_list;

    opendir my $dh, $cwd or die;
      @file_list = grep { -f "$cwd/$_" } readdir $dh;
    closedir $dh;

    my %file_table;
    foreach my $f (@file_list) {
        open my $fh, '<', "$cwd/$f" or next;
        my $contents = do { local $/; <$fh> };
        close $fh;

        $file_table{$f} = $contents;
    }

    $c->stash(
        dir => $cwd,
        items => \%file_table,
    );
    $c->render(template => 'listing');
};

app->start;

__DATA__

@@ listing.html.ep
<!DOCTYPE html>
<html>
<head><title>Welcome</title></head>
<body>
    <h1>Listing of <%= $dir %></h1>
    % foreach my $k (keys %{$items}) {
        <div>
            <h3><%= $k %></h3>
            <pre style="margin-left: 20px"><!--
                --><%= $items->{$k} %>
            </pre>
        </div>
    % }
</body>
</html>
