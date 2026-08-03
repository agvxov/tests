use strict;
use warnings;
use Win32::Clipboard;

my $clip = Win32::Clipboard();

print "Available Clipboard Formats:\n";
my @formats = $clip->EnumFormats();

foreach my $fmt (@formats) {
    print " -- Format ID: $fmt\n";
    print $clip->GetAs($fmt) . "\n";
}
