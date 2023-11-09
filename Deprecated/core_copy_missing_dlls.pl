#!/usr/bin/perl

use strict;
use warnings;
use File::Copy;

# Check for the correct number of command-line arguments
if (@ARGV != 2) {
    die "Usage: $0 <source_directory> <destination_directory>\n";
}

# Get the source and destination directories from command-line arguments
my $source_dir = $ARGV[0];
my $destination_dir = $ARGV[1];

print "Copy process started.\n";
print "Source Directory: $source_dir\n";
print "Destination Directory: $destination_dir\n";

# List all .dll files in the source directory
opendir(my $dh, $source_dir) or die "Could not open directory '$source_dir': $!";
my @dll_files = grep { /\.dll$/i } readdir($dh);
closedir($dh);

print "Found DLL files: @dll_files\n";

# Copy missing .dll files to the destination directory
foreach my $dll_file (@dll_files) {
    my $source_path = "$source_dir/$dll_file";
    my $destination_path = "$destination_dir/$dll_file";
    
    if (!-e $destination_path) {
        copy($source_path, $destination_path) or die "Copy failed: $!";
        print "Copied $dll_file to $destination_dir\n";
    } else {
        print "Skipped $dll_file (already exists in $destination_dir)\n";
    }
}

print "Copy process completed.\n";