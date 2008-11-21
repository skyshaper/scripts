use strict;
use warnings;

use Test::More tests => 3;

my $flamingo_path = "./flamingo";

like(qx(echo "mirrors are more fun than television" | $flamingo_path),
	qr/^mirrorS arE morE fuN thaN televisioN/,
	'flamingo works');

like(qx(echo "She has dyed her hair red!" | $flamingo_path),
	qr/^shE haS dyeD heR haiR reD!/,
	'flamingo works with punctuation');

like(qx(echo "The Flesh of Fallen Angels" | $flamingo_path),
	qr/^thE flesH oF falleN angelS/,
	'flamingo keeps working after 2 tests');
