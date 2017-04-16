#!/usr/bin/python
import dep_lib
import sys
import os
from subprocess import call

dependencyName = 'build_zeromq'
dependencyVersion = "4.2.0"

if len(sys.argv) == 2:
    directory = os.path.abspath(str(sys.argv[1]))
else:
    sys.exit("ERROR directory missing")

srcDir = os.path.join(directory, "zeromq")

print "Boostraping {0}-{1}...".format(dependencyName, dependencyVersion)
call(["./autogen.sh", ''], cwd = srcDir)
call(["./configure", ''], cwd = srcDir)
call(["make", ''], cwd = srcDir)
