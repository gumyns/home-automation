#!/usr/bin/python
import dep_lib
import sys
import os

dependencyName = "zeromq"
dependencyVersion = "4.2.0"

if len(sys.argv) == 2:
	directory = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

dirname = os.path.join(directory, "zeromq-4.2.0")
fname = os.path.join(directory, 'zeromq-4.2.0.tar.gz');

if not dependencyVersion == dep_lib.getVersion(dependencyName) or not os.path.isdir(dirname):
	if not os.path.isfile(fname):
		print "Downloading zeromq-4.2.0..."
		dep_lib.download("https://github.com/zeromq/libzmq/releases/download/v4.2.0/zeromq-4.2.0.tar.gz", fname)
	print "Unziping zeromq..."
	dep_lib.unzipTar(fname, directory)
	print "Removing unnecessary files..."
	os.remove(fname)
	dep_lib.setVersion(dependencyName, dependencyVersion)











