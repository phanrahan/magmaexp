use Test::More;

use Algorithm::Networksort;
use strict;
use warnings;

my $nw = Algorithm::Networksort->new(inputs => 7, algorithm => "hibbard");

eval "use Test::XML::Easy";
if ($@)
{
	plan skip_all => "Test::XML::Easy required for verifying SVG"
}
else
{
	plan tests => 2;
}

	#
	# Start with a simple network.
	#
	my $svg = $nw->graph_svg();

	is_well_formed_xml($svg, "Test with default SVG settings");

	#
	# Now create one that has the defaults changed.
	#
	$nw->title($nw->inputs . " input network using $nw->algorithm");

	$nw->colorsettings(inputbegin=>'red',
		inputend=>'blue',
		compbegin=>'magenta',
		compend=>'teal');

	$nw->graphsettings(
		vt_margin => 25,
		vt_sep => 16,
		indent => 8,
		hz_margin => 20,
		hz_sep => 16,
		stroke_width => 4);

	$svg = $nw->graph_svg();
	is_well_formed_xml($svg, "Test with defaults changed");

