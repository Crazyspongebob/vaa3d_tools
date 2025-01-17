#! /bin/perl
#
# docs/reference/beautify_docs.pl.  Generated from beautify_docs.pl.in by configure.
#

#sub main()
{
  my $directory = ".";
  $directory = $ARGV[0] unless scalar(@ARGV) == 0;
  print "processing directory $directory...\n" unless $directory =~ /^\.?$/;

  foreach(`find "$directory" -type f -name '*.html'`)
  {
    chomp;
    /([^\/]+)$/;
    print "processing $1...\n";
    &process($_);
  }

  exit 0;
}

sub process($)
{
  my ($file) = @_;
  my @outbuf;

  open(FILE, '<', $file);

  while(<FILE>)
  {
    if(/<a class="el"/)
    {
      # return value
      s/ &amp;&nbsp;/&amp;&nbsp;/;
      s/ \*&nbsp;/*&nbsp;/;

      # arg list
      s/ &amp;/&amp;/g;
      s/&amp;\b/&amp; /g;
      s/ \*/*/g;
      s/\*\b/* /g;

      # templates
      s/\btemplate&lt;\b/template &lt;/;
      while(s/(.*&lt;) +(.+) +(&gt;.*)/$1$2$3/) {}
    }
    elsif(/<td class="md(|name)"/)
    {
      # left parenthesis
      s/\(&nbsp;/(/;

      # return value
      s/ &amp; /&amp; /g;
      s/ \* /* /g;

      # arg list
      s/ &amp;&nbsp;/&amp;&nbsp;/g;
      s/ \*&nbsp;/*&nbsp;/g;

      # templates
      s/\btemplate&lt;\b/template &lt;/;
      while(s/(.*&lt;) +(.+) +(&gt;.*)/$1$2$3/) {}
    }
    else
    {
      # template decls
      s/^(|<h\d>)template&lt;\b/$1template &lt;/;
    }

    push(@outbuf, $_);
  }

  open(FILE, '>', $file);

  # write the whole buffer back
  print FILE "$_" foreach(@outbuf);

  close(FILE);
}

