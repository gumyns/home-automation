#!/usr/bin/python
import dep_lib
import sys
import os
import shutil

dependencyName = "zeromq_cpp"
dependencyVersion = "4.2.1"

if len(sys.argv) == 2:
	directory = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

dstDir = os.path.join(directory, "include")
dstFile = os.path.join(dstDir, "v4.2.1.zip")

neededFiles = not dep_lib.filesExist(os.path.join(dstDir, 'zmq.hpp'), os.path.join(dstDir, 'zmq_addon.hpp'))

dep_lib.createDir(dstDir)

if not dependencyVersion == dep_lib.getVersion(dependencyName) or neededFiles:
	print "Downloading {0}-{1}...".format(dependencyName, dependencyVersion)
	dep_lib.download("https://github.com/zeromq/cppzmq/archive/v4.2.1.zip", dstFile)
	print "Uzipping {0}-{1}...".format(dependencyName, dependencyVersion)
	dep_lib.unzipZip(dstFile, dstDir)
	# move needed files
	uName = 'cppzmq-4.2.1'
	os.rename(os.path.join(dstDir, uName, 'zmq.hpp'), os.path.join(dstDir, 'zmq.hpp'))
	os.rename(os.path.join(dstDir, uName, 'zmq_addon.hpp'), os.path.join(dstDir, 'zmq_addon.hpp'))
	print "Removing unnecessary files..."
	shutil.rmtree(os.path.join(dstDir, uName)) # remove all stuff recursivelly
	os.remove(dstFile) # remove zip
	dep_lib.setVersion(dependencyName, dependencyVersion)



