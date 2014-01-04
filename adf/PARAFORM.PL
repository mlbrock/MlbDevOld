	while (<>) {
		chop;
		$in_line    =  $_;
		$in_line    =~ s/Not supported\./NA/;
		@in_data    =  split(/\s+/, $in_line);
		$in_data[0] =  "\"".$in_data[0]."\"";
		$in_data[1] =  ($in_data[1] eq "yes"   ) ? "ADF_TRUE"  : "ADF_FALSE";
		$in_data[2] =  ($in_data[2] eq "normal") ? "ADF_FALSE" : "ADF_TRUE";
		$in_data[3] =  $in_data[3] + 0;
		$in_data[4] =  ($in_data[4] eq "number") ? "ADF_PFORMAT_TYPE_NM" :
			($in_data[4] eq "bullet") ? "ADF_PFORMAT_TYPE_BB" :
			($in_data[4] eq "indent") ? "ADF_PFORMAT_TYPE_IN" :
			(($in_data[4] eq "none") && $in_data[3]) ? "ADF_PFORMAT_TYPE_IN" :
			"ADF_PFORMAT_TYPE_NONE";
		$in_data[5] =  ($in_data[5] eq "yes"   ) ? "ADF_TRUE"  : "ADF_FALSE";
		$in_data[6] =  ($in_data[6] eq "yes"   ) ? "ADF_TRUE"  : "ADF_FALSE";
		$in_data[7] =  ($in_data[7] eq "NA"    ) ? "ADF_FALSE" : "ADF_TRUE";
		print "\t{\n";
		print "\t\t$in_data[0],\t";
		if (length($in_data[0]) <= 7) {
			print "\t";
		}
		print "$in_data[1],\t$in_data[2],\t$in_data[3],\t$in_data[4],\n",
			"\t\t$in_data[5],\t$in_data[6],\t$in_data[7]\n";
		print "\t},\n";
	}

	exit(0);

