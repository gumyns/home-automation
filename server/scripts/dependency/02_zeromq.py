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

dirname = os.path.join(directory, "zeromq")
fname = os.path.join(directory, 'zeromq-4.2.0.tar.gz');

if not dependencyVersion == dep_lib.getVersion(dependencyName) or not os.path.isdir(dirname):
	if not os.path.isfile(fname):
		print "Downloading {0}-{1}...".format(dependencyName, dependencyVersion)
		dep_lib.download("https://github.com/zeromq/libzmq/releases/download/v4.2.0/zeromq-4.2.0.tar.gz", fname)
	print "Uzipping {0}-{1}...".format(dependencyName, dependencyVersion)
	dep_lib.unzipTar(fname, directory)
	os.rename(os.path.join(directory, "zeromq-4.2.0"), dirname)
	print "Removing unnecessary files..."
	os.remove(fname)
	dep_lib.setVersion(dependencyName, dependencyVersion)











