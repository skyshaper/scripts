# Copyright (c) 2008 Vsevolod Kozlov <zaba@thorium.homeunix.org>
# License: Public domain.
use strict;
use warnings;

use Test::More tests => 3;

my $natopat_path = './natopat';

# Test 1
my $test1_output = qx($natopat_path < t/natopat/test1);
chomp $test1_output;
is($test1_output, "Alpha bravo Charlie",
	'value is converted correctly');

# Test 2
my $test2_output = qx($natopat_path -r < t/natopat/test2);
chomp $test2_output;
is($test2_output, "AbCdEfGhIjKlMnOpQrStUvWxYz",
	'value is converted back correctly');

# Test 3
my $test3_output = qx($natopat_path < t/natopat/test3 | $natopat_path -r);
my $test3_expect = qx(cat t/natopat/test3);
chomp($test3_output, $test3_expect);
is($test3_output, $test3_expect, 'value is converted back and forth correctly')
