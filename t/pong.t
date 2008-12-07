use strict;
use warnings;
use Test::Exception;
use Test::More tests => 3;
use IPC::Open3;

my ($pong, $pong_out, $pong_in);

lives_ok { $pong = open3($pong_in, $pong_out, $pong_out, './pong') } 'ran ./pong';

cmp_ok(<$pong_out>, 'eq', "|.\n", "first output line is correct");

print $pong_in ".|\n";
my $input = <$pong_out>;
diag("Second line: $input");

print $pong_in "invalid\n";
$input = <$pong_out>;
like($input, qr/^You lose/, 'valid message upon failure');
