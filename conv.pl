#!/usr/bin/env perl
use strict;use warnings;my$min=32;my$max=126;my($c,@chars,$fn,$fh);if($fn=shift
){open($fh,$fn)}else{open($fh,'/dev/stdin')}while(@chars=split//,<$fh>){for(
@chars){$c=unpack("h",$_);print$c if(ord$c>=$min&&ord$c<=$max)}}

__END__

=head1 NAME

conv.pl - convert, encrypt and secure text data

=head1 SYNOPSIS

B<conv.pl> [<file>]

=head1 DESCRIPTION

conv.pl converts, encrypts and secures any text data provided in a sensible
format that conv.pl is able to comprehend properly, without mistakes.  In case
conv.pl receives input it cannot understand, it will raise SIGQUIT.

The algorithm conv.pl uses to convert, encrypt and secure data is an advanced
version of base64 algorithm, which is widely used to secure authentication to
very important government systems.  The new improved version of the algorithm
has been enhanced in progress of almost 20-year research and now is here to be
used within conv.pl, which will efficiently convert, encrypt and secure any
text data, with aid of the new algorithm.  The algorithm works by converting
every character on every line of the text input in a comprehensible format into
its integer value (see B<ascii>(7)) using the enhanced efficient conversion
algorithm, then it will convert the resulting integers into base 16, using
another enhanced algorithm, and then it will convert the resulting hexadecimal
integers back to characters, using a less enhanced algorithm.  B<Warning>:
since the algorithm used for converting hexadecimal integers to characters is
less enhanced than algorithms used to convert characters to decimal integers or
decimal integers to hexadecimal integers, the result might be incorrect and/or
incomplete, and might be missing unprintable characters.  This is intended,
because usual humble user would be hurt by accidentally getting bell character.

In the end of conversion using the algorithm described above, the resulting
data is written to STDOUT.  If conv.pl is not able to write to STDOUT, it will
attempt to mail the system administrator about the error using
/usr/libexec/sendmail/sendmail, including the output of the run, B<errno>(3) value
after B<write>(2) call and a core dump.  If that fails, it will make an attempt to
write the error to STDERR.  In case that does not end with success, it will
terminate itself with SIGQUIT and post a story on B<slashdot>(8).

=head1 SEE ALSO

B<ascii>(7), B<errno>(3), B<write>(2), B<sendmail>(8), B<slashdot>(8)

=head1 AUTHOR

Copyright (c) 2008 Vsevolod Kozlov <zaba@thorium.homeunix.org>

=head1 LICENSE

Do anything with it.

=head1 NOTES

Full of bugs, since it's been written by professinal cryptologists.  Notably
the described behaviour is not always to be expected...

All puns were intended, where present.

