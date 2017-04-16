#!/usr/bin/python
import dep_lib
import sys
import os

dependencyName = "json"
dependencyVersion = "2.0.10"

if len(sys.argv) == 2:
	directory = os.path.abspath(str(sys.argv[1]))
else:
	sys.exit("ERROR directory missing");

dstDir = os.path.join(directory, "include")
dstFile = os.path.join(dstDir, "json.hpp")

dep_lib.createDir(dstDir)

if not dependencyVersion == dep_lib.getVersion(dependencyName) or not os.path.isfile(dstFile):
	print "Downloading json.hpp..."
	dep_lib.download("https://raw.githubusercontent.com/nlohmann/json/v2.0.10/src/json.hpp", dstFile)
	dep_lib.setVersion(dependencyName, dependencyVersion)	

