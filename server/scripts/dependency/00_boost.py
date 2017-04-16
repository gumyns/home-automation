#!/usr/bin/python
import dep_lib
import sys
import os

dependencyName = "boost"
dependencyVersion = "1.63.0"

if len(sys.argv) == 2:
	directory = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

dirname = os.path.join(directory, "boost_1_63_0")
fname = os.path.join(directory, 'boost.tar.bz2');

if not dependencyVersion == dep_lib.getVersion(dependencyName) or not os.path.isdir(dirname):
	if not os.path.isfile(fname):
		print "Downloading {0}-{1}...".format(dependencyName, dependencyVersion)
		dep_lib.download("https://sourceforge.net/projects/boost/files/boost/1.63.0/boost_1_63_0.tar.bz2", fname)
	print "Uzipping {0}-{1}...".format(dependencyName, dependencyVersion)
	dep_lib.unzipTar(fname, directory)
	print "Removing unnecessary files..."
	os.remove(fname)
	dep_lib.setVersion(dependencyName, dependencyVersion)












